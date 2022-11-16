# Assignment 1: Basic Linear Algebra Routines

## Getting Started

The objective of this exercise is
for you to familiarize with [CMake] and [Catch],
two powerful tools used in this project.

1. Run the benchmarks for the builtin linear algebra routines
  with 10 samples per benchmark
  and create a table comparing the complexity of the different routines.
2. Implement the functions defined in the header [`problem_1.hpp`].
3. Check that all the tests pass.

[CMake]: https://cmake.org/
[Catch]: https://github.com/catchorg/Catch2
[`problem_1.hpp`]: /../user/assignment_1/problem_1.hpp

## Cache-Friendly Implementations

The objective of this exercise is
learning to program caché friendly versions of some algorithms.
We will be focusing on matrix multiplication and LU factorization.
The tasks are listed below.

1. Implement the following routines in the file [`linalg.hpp`].
  1. Block General Matrix Multiplication (GEMM).
  2. LU factorization.
  3. Block LU factorization.
2. Benchmark the cache friendly versions aggainst standard versions.
You may use the test benchmark.
Compare for at least 10 samples.
The Catch framework takes care of the warm up.

You can use the linalg tests to check the correctness of your functions.

[`linalg.hpp`]: /../include/hpc_tutor/linalg.hpp
