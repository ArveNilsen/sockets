#pragma once

#include "RawSocket.hpp"

template <typename Sys>
class SocketFactory {
public:
    explicit SocketFactory(const Sys& sys = Sys{}) : sys_(sys) {}

    RawSocket create_tcp() const {
// These preprosessor conditionals are needed to support MacOS.
// TODO: Consider not supporting MacOS.
#ifdef SOCK_CLOEXEC
    int flags = SOCK_STREAM | SOCK_CLOEXEC;
    int fd = sys_.socket(AF_INET, flags, 0);
#else
    int fd = sys_.socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (fd == -1) 
        throw std::system_error(errno, std::system_category(), "socket");
#ifndef SOCK_CLOEXEC
    int f = sys_.fcntl(fd, F_GETFD, 0);
    if (f == -1) { 
        sys_.close(fd);
        throw std::system_error(errno, std::system_category(), "fcntl(F_GETFD)");
    }

    if (sys_.fcntl(fd, F_SETFD, f | FD_CLOEXEC) == -1) {
        sys_.close(fd);
        throw std::system_error(errno, std::system_category(), "fcntl(F_SETFD)");
    }
#endif

    return RawSocket(fd);
}

private:
    Sys sys_;
};

