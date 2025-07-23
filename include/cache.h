#ifndef CACHE_H
#define CACHE_H

#include <cstdint>
#include <vector>
#include <deque>

class Cache {
public:
    // Construtor:
    // nsets: número de conjuntos;
    // bsize: tamanho do bloco (em bytes);
    // assoc: grau de associatividade;
    // subst: política de substituição ('F' para FIFO, 'L' para LRU)
    Cache(int nsets, int bsize, int assoc, char subst);

    // Processa o acesso a um endereço (32 bits)
    void acessarEndereco(uint32_t endereco);

    // Exibe as estatísticas da simulação (flagSaida: 0 = formato detalhado, 1 = formato compacto)
    void exibirEstatisticas(int flagSaida) const;

private:
    int nsets;   // Número de conjuntos
    int bsize;   // Tamanho do bloco (bytes)
    int assoc;   // Grau de associatividade
    char politicaSubst; // 'F' para FIFO ou 'L' para LRU

    int bitsOffset; // Bits de deslocamento
    int bitsIndice;  // Bits para o índice
    int bitsTag;    // Bits para a tag

    int totalAcessos;
    int acertos;
    int missesCompulsorios;
    int missesCapacidade;
    int missesConflito;

    int blocosOcupados; // Quantidade de blocos já ocupados na cache
    int totalBlocos;      // Total de blocos (nsets * assoc)

    // Representação de um bloco da cache
    struct Bloco {
        uint32_t tag;
        bool valido;
    };

    // Vetor de conjuntos – cada conjunto é um vetor de blocos
    std::vector< std::vector<Bloco> > conjuntos;
    // Para cada conjunto, um deque que armazena os índices das vias na ordem de acesso.
    // Para FIFO, a ordem é de inserção; para LRU, o bloco mais recentemente usado fica no final.
    std::vector< std::deque<int> > ordem;
};

#endif // CACHE_H
