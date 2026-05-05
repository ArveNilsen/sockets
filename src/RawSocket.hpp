#pragma once

#include <system_error>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct RawSocket {
    using native_handle_type = int;

    RawSocket() = delete;
    explicit RawSocket(native_handle_type fd) noexcept : fd_(fd) {}
    ~RawSocket() { if (fd_ != -1) ::close(fd_); }

    RawSocket(const RawSocket&) = delete;
    RawSocket& operator=(const RawSocket&) = delete;

    RawSocket(RawSocket&& o) noexcept : fd_(o.fd_) { o.fd_ = -1; }
    RawSocket& operator=(RawSocket&& o) noexcept {
        if (this != &o) {
            if (fd_ != -1) ::close(fd_);
            fd_ = o.fd_;
            o.fd_ = -1;
        }
        return *this;
    }
    
    native_handle_type native_handle() const noexcept { return fd_; }

    native_handle_type release() noexcept {
        native_handle_type temp = fd_;
        fd_ = -1;
        return temp;
    }

    bool valid() const noexcept { return fd_ != -1; }

    static RawSocket create_tcp() {
// These preprosessor conditionals are needed to support MacOS.
// TODO: Consider not supporting MacOS.
#ifdef SOCK_CLOEXEC
        int flags = SOCK_STREAM | SOCK_CLOEXEC;
        int fd = ::socket(AF_INET, flags, 0);
#else
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
#endif
        if (fd == -1) 
            throw std::system_error(errno, std::system_category(), "socket");
#ifndef SOCK_CLOEXEC
        int f = fcntl(fd, F_GETFD);
        if (f == -1) { 
            ::close(fd);
            throw std::system_error(errno, std::system_category(), "fcntl(F_GETFD)");
        }

        if (fcntl(fd, F_SETFD, f | FD_CLOEXEC) == -1) {
            ::close(fd);
            throw std::system_error(errno, std::system_category(), "fcntl(F_SETFD)");
        }
#endif

        return RawSocket(fd);
    }

    native_handle_type fd_{ - 1 };
};
