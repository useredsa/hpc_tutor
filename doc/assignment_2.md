# Assignment 2: Thread-Level Parallelism

## Description

The objective of this assignment is to learn about thread-level parallelism.
Your task is implementing parallel versions
of the linear algebra routines
using OpenMP.

## Steps

1. Implement the parallel versions of the linear algebra routines
that are missing in the library header [`hpc_tutor/linalg_t.hpp`].
2. Test correctness using the tests in [`test/linalg_t_tests.cpp`].
3. Measure the speed-up using the benchmarks
in [`test/linalg_t_benchmarks.cpp`].

[OpenMP]: https://www.openmp.org/
[`hpc_tutor/linalg_t.hpp`]: /../include/hpc_tutor/linalg_t.hpp
[`test/linalg_t_tests.cpp`]: /../test/linalg_t_tests.cpp
[`test/linalg_t_benchmarks.cpp`]: /../test/linalg_t_benchmarks.cpp
