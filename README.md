# Memory Repair

This program utilizes max flow min cost and minimum weighted vertex cover algorithm to tackle the m-CNT fixing problem.

* Platform: Linux
* Prerequisite: cmake >= 3.0

## Compile

```bash
mkdir build; cd build
cmake ..
make
make test
```

## Useage

Setting File:

```
column row
row-segments column-segments 
row-sparing-lines column-sparing-lines
sharing-cost
```

where spare row segments is the segments alone columns and the variable in source code is spare_c.

mCNT File:

```
ri cj  
....
```
where ri ranges from 0 to r - 1 and cj from 0 to c - 1. Each line contains exactly one fault.

Baseline Demo:

```sh
./MemRepairBaselineDemo setting_file_path mcnt_file_path
```

The baseline algorithm utilizes greed strategy in determining weights of vertices in bipartite graph to ensure the minimum weighted vertex cover will yield some solution for each block.

Baseline Benchmark:
```sh
./run_benchmark_once benchmark_id
```

For file benchmark_setting_file_5_1 the benchmark_id equals 5_1.