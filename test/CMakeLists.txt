add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(matrix_tests)

add_executable(linalg_tests linalg_tests.cpp)
target_link_libraries(linalg_tests PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(linalg_tests)

add_executable(linalg_benchmarks linalg_benchmarks.cpp)
target_link_libraries(linalg_benchmarks PRIVATE hpc_tutor Catch2::Catch2WithMain)

add_executable(linalg_t_tests linalg_t_tests.cpp)
target_link_libraries(linalg_t_tests
  PRIVATE hpc_tutor Catch2::Catch2WithMain OpenMP::OpenMP_CXX)
catch_discover_tests(linalg_t_tests)

# add_executable(linalg_t_benchmarks linalg_t_benchmarks.cpp)
# target_link_libraries(linalg_t_benchmarks
#   PRIVATE hpc_tutor Catch2::Catch2WithMain OpenMP::OpenMP_CXX)
