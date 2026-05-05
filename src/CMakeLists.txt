add_executable(main)

target_sources(main
    PRIVATE
        main.cpp
    PUBLIC 
        FILE_SET HEADERS
        BASE_DIRS ../include
        FILES
            ../include/sockets/BoundSocket.hpp
            ../include/sockets/RawSocket.hpp
            ../include/sockets/SocketFactory.hpp
            ../include/sockets/SysPolicy.hpp
)

target_link_libraries(main
    PRIVATE
        sockets::project_warnings
        sockets::project_options
)
