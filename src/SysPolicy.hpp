#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

struct SysPosix {
    int socket(int domain, int type, int protocol) const noexcept {
        return ::socket(domain, type, protocol);
    }

    int fcntl(int fd, int cmd, int arg) const noexcept {
        return ::fcntl(fd, cmd, arg);
    }

    int close(int fd) const noexcept {
        return ::close(fd);
    }
};
