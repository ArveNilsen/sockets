add_library(project_warnings INTERFACE)
add_library(sockets::project_warnings ALIAS project_warnings)
target_compile_options(project_warnings
    INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual 
        -Wpedantic 
        -Wconversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Wimplicit-fallthrough

        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches 
        -Wlogical-op 
        -Wuseless-cast 
        -Wsuggest-override
)

