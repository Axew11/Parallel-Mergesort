# Parallel-Mergesort-Benchmark

This is a single/parallel mergesort benchmark for the CPU. It will mergesort a given vector of size n with random ints from 1 to 1 million inclusive. There are two command-line arguments to pass in running the program.

Format:
`./mergesort_benchmark number_of_threads number_of_ints_to_sort`

Example:
![](mergesort_benchmark_demo.gif)

Cases where it will not run:
  - If you provide more threads than your hardware supports
  - If you're parallelizing with a number of integers that doesn't evenly divide with the number of threads you want
  - If you provide a number of threads that isn't a power of two
