#include <iostream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "cache.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    if (!argValido(argc, argv)) {
        return 1;
    }
    
    // Semente para geração de números aleatórios (para RANDOM)
    srand(time(nullptr));
    
    int  nsets           = std::stoi(argv[1]);
    int  bsize           = std::stoi(argv[2]);
    int  assoc           = std::stoi(argv[3]);
    char subst          = std::toupper(argv[4][0]); // 'F' para FIFO, 'L' para LRU, 'R' para RANDOM
    int  flag_saida      = std::stoi(argv[5]);
    std::string arquivo = argv[6];

    // Cria a cache com a política de substituição desejada
    Cache cache(nsets, bsize, assoc, subst);

    // Lê os endereços do arquivo binário
    std::vector<uint32_t> enderecos = lerArqBin(arquivo);
    for (uint32_t endereco : enderecos) {
        cache.acessarEndereco(endereco);
    }
    
    // Exibe as estatísticas da simulação
    cache.exibirEstatisticas(flag_saida);
    
    return 0;
}
