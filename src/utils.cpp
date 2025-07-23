#include <iostream>
#include "utils.h"
#include <cmath>
#include <fstream>
#include <string>
#include <stdexcept> // Para std::invalid_argument
#include <vector>
#include <cstdint>

// Função auxiliar para verificar se um número é potência de 2
bool potenciaDois(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Valida argumentos passados por linha de comando
bool argValido(int argc, char* argv[]) {
    int  nsets, bsize, assoc, flagSaida;
    char subst;
    std::string arquivo;

    // Verifica número de argumentos
    if (argc != 7) {
        std::cerr << "Erro: Número incorreto de argumentos.\n";
        std::cerr << "Uso: " << argv[0] << " <nsets> <bsize> <assoc> <substituição> <flag_saida> <arquivo_entrada>\n";
        return false;
    }

    // Converte argumentos para inteiros
    try {
        nsets     = std::stoi(argv[1]);
        bsize     = std::stoi(argv[2]);
        assoc     = std::stoi(argv[3]);
        subst     = toupper(argv[4][0]); // Aceita 'r', 'f', 'l' minúsculos
        flagSaida = std::stoi(argv[5]);
        arquivo   = argv[6];
    } catch (...) {
        std::cerr << "Erro: Argumentos inválidos (não são números inteiros).\n";
        return false;
    }

    // Valida nsets (número de conjuntos), bsize (tamanho do bloco), assoc (associatividade)
    if (nsets <= 0 || bsize <= 0 || assoc <= 0) {
        std::cerr << "Erro: nsets, bsize e assoc devem ser maiores que zero.\n";
        return false;
    }

    // Valida potências de 2 (exceto assoc = 1 para mapeamento direto)
    if (!potenciaDois(nsets) || !potenciaDois(bsize)) {
        std::cerr << "Erro: nsets e bsize devem ser potências de 2.\n";
        return false;
    }

    // Valida política de substituição
    if (subst != 'R' && subst != 'F' && subst != 'L') {
        std::cerr << "Erro: Política de substituição inválida. Use R (Random), F (FIFO) ou L (LRU).\n";
        return false;
    }

    // Valida flagSaida
    if (flagSaida != 0 && flagSaida != 1) {
        std::cerr << "Erro: flag_saida deve ser 0 ou 1.\n";
        return false;
    }

    // Valida arquivo de entrada
    std::ifstream file(arquivo, std::ios::binary);
    if (!file.good()) {
        std::cerr << "Erro: Arquivo de entrada '" << arquivo << "' não encontrado ou inválido.\n";
        return false;
    }
    file.close();

    return true;
}

// Faz os calculos necessários para usar os bits
void calcBits(int bsize, int nsets, int &offsetBits, int &indexBits, int &tagBits) {
    try {
        offsetBits  = log2(bsize);
        indexBits   = log2(nsets);
        tagBits     = 32 - offsetBits - indexBits;
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Erro em calcularBits: " + std::string(e.what()));
    }
}

std::vector<uint32_t> lerArqBin(const std::string &nomeArq) {
    std::ifstream file(nomeArq, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Erro ao abrir o arquivo: " + nomeArq);
    }

    std::vector<uint32_t> enderecos;
    uint32_t endereco;

    // Lê 4 bytes (32 bits) por vez
    while (file.read(reinterpret_cast<char*>(&endereco), sizeof(uint32_t))) {
        // Converte de big-endian para little-endian (se necessário)
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            endereco = __builtin_bswap32(endereco);
        #endif
        enderecos.push_back(endereco);
    }

    return enderecos;
}