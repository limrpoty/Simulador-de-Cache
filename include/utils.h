#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cstdint>
#include <string>

bool argValido(int argc, char *argv[]);
void calcBits(int bsize, int nsets, int &bits_offset, int &bits_indice, int &bits_tag);
std::vector<uint32_t> lerArqBin(const std::string &nomeArq);

#endif // UTILS_H