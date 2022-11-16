cmake_minimum_required(VERSION 3.10)

project(hpc_tutor
  VERSION     0.1.0
  DESCRIPTION "C++ demo project aimed to teach students about hpc"
  LANGUAGES   CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(user/assignment_1)
