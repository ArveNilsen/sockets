#include <iostream>
#include <arpa/inet.h>

#include <sockets/RawSocket.hpp>
#include <sockets/SocketFactory.hpp>
#include <sockets/BoundSocket.hpp>
#include <sockets/SysPolicy.hpp>

int main()
{
    SocketFactory<SysPosix> factory;
    RawSocket rs = factory.create_tcp();

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // TODO: Needs a cleaner api, hide the details
    BoundSocket bound = factory.bind_address(std::move(rs), 
            reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    int fd = bound.native_handle();

    std::cout << "BoundSocket fd: " << fd << "\n";
    return 0;
}
