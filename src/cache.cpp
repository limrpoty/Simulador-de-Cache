#include "cache.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace std;

Cache::Cache(int nsets, int bsize, int assoc, char subst)
    : nsets(nsets), bsize(bsize), assoc(assoc),
      politicaSubst(std::toupper(subst)),
      totalAcessos(0), acertos(0),
      missesCompulsorios(0), missesCapacidade(0), missesConflito(0),
      blocosOcupados(0)
{
    totalBlocos = nsets * assoc;

    // Calcula os bits para offset, índice e tag (assume endereços de 32 bits)
    calcBits(bsize, nsets, bitsOffset, bitsIndice, bitsTag);
    // Inicializa cada conjunto: vetor de blocos, inicialmente inválidos
    conjuntos.resize(nsets, vector<Bloco>(assoc, {0, false}));
    // Se a política for FIFO ou LRU, inicializa o deque de ordem para cada conjunto
    if (politicaSubst == 'F' || politicaSubst == 'L') {
        ordem.resize(nsets);
    }
}

void Cache::acessarEndereco(uint32_t endereco) {
    totalAcessos++;

    // Extrai a tag e o índice do endereço
    uint32_t tag    = endereco >> (bitsOffset + bitsIndice);
    uint32_t indice = (endereco >> bitsOffset) & ((1 << bitsIndice) - 1);

    // Procura o bloco no conjunto
    int via_encontrada = -1;
    for (int via = 0; via < assoc; via++) {
        if (conjuntos[indice][via].valido && conjuntos[indice][via].tag == tag) {
            via_encontrada = via;
            break;
        }
    }

    if (via_encontrada != -1) { // HIT
        acertos++;
        // Se a política for LRU, atualiza a ordem: remove a via e a reinsere no final
        if (politicaSubst == 'L') {
            auto &fila = ordem[indice];
            for (auto iterator = fila.begin(); iterator != fila.end(); ++iterator) {
                if (*iterator == via_encontrada) {
                    fila.erase(iterator);
                    break;
                }
            }
            fila.push_back(via_encontrada);
        }
        return;
    }

    // MISS: procura uma via vazia no conjunto
    int via_vazia = -1;
    for (int via = 0; via < assoc; via++) {
        if (!conjuntos[indice][via].valido) {
            via_vazia = via;
            break;
        }
    }

    if (via_vazia != -1) {
        // Miss compulsório
        missesCompulsorios++;
        conjuntos[indice][via_vazia].tag = tag;
        conjuntos[indice][via_vazia].valido = true;
        if (politicaSubst == 'F' || politicaSubst == 'L') {
            ordem[indice].push_back(via_vazia);
        }
        blocosOcupados++;
    } else {
        // Conjunto cheio
        int via_substituir;
        if (politicaSubst == 'R') {
            // Seleciona um índice aleatório entre 0 e (assoc - 1)
            via_substituir = rand() % assoc;
        } else {
            // Seleciona o bloco no início do deque (o mais antigo ou o menos recentemente usado)
            via_substituir = ordem[indice].front();
            ordem[indice].pop_front();
        }
        conjuntos[indice][via_substituir].tag = tag;
        if (politicaSubst == 'F' || politicaSubst == 'L') {
            ordem[indice].push_back(via_substituir);
        }
        if (blocosOcupados == totalBlocos) {
            missesCapacidade++;
        } else {
            missesConflito++;
        }
    }
}

void Cache::exibirEstatisticas(int flagSaida) const {
    int    totalMisses               = missesCompulsorios + missesCapacidade + missesConflito;
    double taxaHit                   = (totalAcessos > 0) ? static_cast<double>(acertos) / totalAcessos : 0.0;
    double taxaMisses                = 1.0 - taxaHit;
    double taxaMissesCapacidade      = (totalMisses > 0) ? static_cast<double>(missesCapacidade) / totalMisses : 0.0;
    double taxaMissesCompulsorios    = (totalMisses > 0) ? static_cast<double>(missesCompulsorios) / totalMisses : 0.0;
    double taxaMissesConflito        = (totalMisses > 0) ? static_cast<double>(missesConflito) / totalMisses : 0.0;

    if (flagSaida == 0) {

        std::cout << "+-------------------+-------------------+\n";
        std::cout << "|    Estatísticas   |      Valores      |\n";
        std::cout << "+-------------------+-------------------+\n";

        std::cout << std::left; //Para mudar o alinhamento para esquerda

        std::cout << "| Acessos           | " << std::setw(18) << totalAcessos << "|\n";
        std::stringstream ssTaxaHit;
        ssTaxaHit << acertos << " (" << std::fixed << std::setprecision(2)           << taxaHit * 100 << "%)";
        std::cout << "| Hits              | " << std::setw(18) << ssTaxaHit.str()    << "|\n";
        std::cout << "| Misses            | " << std::setw(18) << totalMisses        << "|\n";
        std::cout << "| Compulsórios      | " << std::setw(18) << missesCompulsorios << "|\n";
        std::cout << "| Capacidade        | " << std::setw(18) << missesCapacidade   << "|\n";
        std::cout << "| Conflito          | " << std::setw(18) << missesConflito     << "|\n";
        std::cout << "+-------------------+-------------------+\n";
    } else {
        // Formatação conforme output pedido
        printf("%d %.4lf %.4lf %.2lf %.2lf %.2lf\n",
               totalAcessos, taxaHit, taxaMisses,
               taxaMissesCompulsorios, taxaMissesCapacidade, taxaMissesConflito);
    }
}
