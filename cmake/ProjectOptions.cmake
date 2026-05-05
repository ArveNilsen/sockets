add_library(project_options INTERFACE)
add_library(sockets::project_options ALIAS project_options)
target_compile_features(project_options 
    INTERFACE 
    cxx_std_${CMAKE_CXX_STANDARD}
)

