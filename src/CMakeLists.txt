add_executable(main)

target_sources(main
    PRIVATE
        main.cpp
)

target_link_libraries(main
    PRIVATE
        sockets::project_warnings
        sockets::project_options
)
