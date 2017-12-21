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
row column
row-segments column-segments
row-sparing-lines column-sparing-lines
sharing-cost
```

mCNT File:

```
ri cj  
....
```
where ri ranges from 0 to r - 1 and cj from 0 to c - 1

Baseline Demo:

```cpp
./MemRepairBaselineDemo setting_file_path mcnt_file_path
```

The baseline algorithm utilizes greed strategy in determining weights of vertices in bipartite graph to ensure the minimum weighted vertex cover will yield some solution for each block.