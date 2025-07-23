## Simulador de Cache

Um simulador de cache em C++ que permite o teste de diferentes configurações e políticas de substituição.

## Uso

```bash
./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada
```

#### Parâmetros

- ***cache_simulator:*** Nome do arquivo de execução principal do simulador
- nsets: Número de conjuntos na cache (número total de “linhas” ou “entradas” da cache)
- bsize: Tamanho do bloco em bytes
- assoc: Grau de associatividade (número de vias ou blocos que cada conjunto possui)
- substituição: Política de substituição
	- `R` - Random 
	- `F` - FIFO (First In First Out)
	- `L` LRU (Least Recently Used )
- f lag_saida: Flag de saída dos dados
	- `0`  - Saída com textos para melhor visualização
	- `1` - Formato padrão seguindo a seguinte ordem: total de acessos, taxa de hit, taxa de miss, taxa de miss compulsório, taxa de miss de capacidade, taxa de miss de conflito
- arquivo_de_entrada: Arquivo com os endereços para acesso à cache

##### Arquivo de Entrada

O arquivo de entrada será utilizado como entrada para o simulador (armazenado em formato binário) que conterá os endereços requisitados à cache (cada endereço possui 32 bits, em formato big endian).


### Exemplos de Uso

A pasta `testes` contém alguns arquivos no formato binário exigido e em .txt para facilitar a visualização dos valores e o entendimento do comportamento da cache.

#### Exemplo 1: 

```bash
./cache_simulator 256 4 1 R 1 testes/bin_100.bin
```

- Resultado: 
	- flag 1: `100 0.9200 0.0800 1.00 0.00 0.00`
	- flag 0:  
		- <img src="https://github.com/limrpoty/Simulador-de-Cache/blob/main/imagens/exemplo_1.png" alt="Exemplo 1 - Tabela">

#### Exemplo 2:

```bash
./cache_simulator 512 8 2 R 1 testes/vortex.in.sem.persons.bin
```

- Resultado:
	- flag 1: `186676 0.8787 0.1213 0.05 0.93 0.02`
	- flag 0:
		- <img src="https://github.com/limrpoty/Simulador-de-Cache/blob/main/imagens/exemplo_2.png" alt="Exemplo 2 - Tabela">

## Autores
- Fabrício Barbosa Viegas
- Marcos Lima Alves
