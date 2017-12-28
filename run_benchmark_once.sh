#!/bin/bash

benchmark() {
	echo "benchmark $1"
	eval "./build/src/MemRepairBaselineBenchmark test/benchmark_setting_file_$1.txt test/fault_distr.txt"
}

benchmark $1