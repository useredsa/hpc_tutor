Include(FetchContent)

# CMake + Catch2 usage refence:
# https://github.com/catchorg/Catch2/blob/v3.1.1/docs/cmake-integration.md
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(Catch2)
