## Cache Simulator

A C++ cache simulator that allows testing of different configurations and replacement policies.

## Usage

```bash
./cache_simulator <nsets> <bsize> <assoc> <replacement> <output_flag> input_file
```

#### Parameters

- ***cache_simulator:*** Name of the main executable file for the simulator
- nsets: Number of sets in the cache (total number of “lines” or “entries” in the cache)
- bsize: Block size in bytes
- assoc: Associativity degree (number of ways or blocks each set contains)
- replacement: Replacement policy
	- `R` - Random 
	- `F` - FIFO (First In First Out)
	- `L` - LRU (Least Recently Used)
- output_flag: Output data flag
	- `0` - Output with descriptive text for better visualization
	- `1` - Standard format following this order: total accesses, hit rate, miss rate, compulsory miss rate, capacity miss rate, conflict miss rate
- input_file: File containing addresses to be accessed in the cache

##### Input File

The input file will be used as input for the simulator (stored in binary format) and contains the requested cache addresses (each address is 32 bits, in big-endian format).

### Usage Examples

The `testes` folder contains some files in the required binary format and corresponding .txt files to facilitate visualization of values and understanding of cache behavior.

#### Example 1:

```bash
./cache_simulator 256 4 1 R 1 testes/bin_100.bin
```

- Result:
	- flag 1: `100 0.9200 0.0800 1.00 0.00 0.00`
	- flag 0:  
		- <img src="https://github.com/limrpoty/Simulador-de-Cache/blob/main/imagens/exemplo_1.png" alt="Example 1 - Table">

#### Example 2:

```bash
./cache_simulator 512 8 2 R 1 testes/vortex.in.sem.persons.bin
```

- Result:
	- flag 1: `186676 0.8787 0.1213 0.05 0.93 0.02`
	- flag 0:
		- <img src="https://github.com/limrpoty/Simulador-de-Cache/blob/main/imagens/exemplo_2.png" alt="Example 2 - Table">

## Authors
- Fabrício Barbosa Viegas
- Marcos Lima Alves
