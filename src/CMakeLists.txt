add_library(hpc_tutor INTERFACE)

target_include_directories(hpc_tutor INTERFACE ../include/)
set_target_properties(hpc_tutor PROPERTIES
  INTERPROCEDURAL_OPTIMIZATION TRUE
)
target_compile_features(hpc_tutor INTERFACE cxx_std_20)
