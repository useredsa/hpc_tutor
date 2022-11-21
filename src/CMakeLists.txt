add_library(hpc_tutor INTERFACE)

target_include_directories(hpc_tutor INTERFACE ../include/)

target_compile_features(hpc_tutor INTERFACE cxx_std_20)
