add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(matrix_tests)

add_executable(assignment_1_tests assignment_1_tests.cpp)
target_link_libraries(assignment_1_tests
  PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(assignment_1_tests)

add_executable(assignment_1_benchmarks assignment_1_benchmarks.cpp)
target_link_libraries(assignment_1_benchmarks
  PRIVATE hpc_tutor Catch2::Catch2WithMain)

add_executable(assignment_2_tests assignment_2_tests.cpp)
target_link_libraries(assignment_2_tests
  PRIVATE hpc_tutor Catch2::Catch2WithMain OpenMP::OpenMP_CXX)
catch_discover_tests(assignment_2_tests)

# add_executable(assignment_2_benchmarks assignment_2_benchmarks.cpp)
# target_link_libraries(assignment_2_benchmarks
#   PRIVATE hpc_tutor Catch2::Catch2WithMain OpenMP::OpenMP_CXX)
