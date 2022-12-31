cmake_minimum_required(VERSION 3.10)

project(hpc_tutor
  VERSION     0.1.0
  DESCRIPTION "C++ demo project aimed to teach students about hpc"
  LANGUAGES   CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
endif()

include(FetchContent)

# CMake + Catch2 usage refence:
# https://github.com/catchorg/Catch2/blob/v3.1.1/docs/cmake-integration.md
fetchcontent_declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.1
)
fetchcontent_makeavailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(user/assignment_1)
