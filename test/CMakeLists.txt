Include(FetchContent)

# CMake + Catch2 usage refence:
# https://github.com/catchorg/Catch2/blob/v3.1.1/docs/cmake-integration.md
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(matrix_tests)

add_executable(linalg_tests linalg_tests.cpp)
target_link_libraries(linalg_tests PRIVATE hpc_tutor Catch2::Catch2WithMain)
catch_discover_tests(linalg_tests)

add_executable(linalg_benchmarks linalg_benchmarks.cpp)
target_link_libraries(linalg_benchmarks PRIVATE hpc_tutor Catch2::Catch2WithMain)
