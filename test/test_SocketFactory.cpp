#include <catch2/catch_test_macros.hpp>
#include "../src/SocketFactory.hpp"
#include <vector>
#include <string>

struct SysMock {
    int socket_ret{ -1 };
    int socket_errno{ 0 };
    int fcntl_getfd_ret{ 0 };
    int fcntl_setfd_ret{ 0 };
    int fcntl_errno{ 0 };
    mutable std::vector<int> closed_fds;

    int socket(int, int, int) const noexcept {
        if (socket_ret == -1) { errno = socket_errno; }
        return socket_ret;
    }

    int fcntl(int fd, int cmd, int arg) const noexcept {
        if (cmd == F_GETFD) {
            if (fcntl_getfd_ret == -1) { errno = fcntl_errno; return -1; }
            return fcntl_getfd_ret;
        }

        if (cmd == F_SETFD) {
            if (fcntl_getfd_ret == -1) { errno = fcntl_errno; return -1; }
            return fcntl_getfd_ret;
        }
        
        return -1;
    }

    int close(int fd) const noexcept {
        closed_fds.push_back(fd);
        return 0;
    }
};

TEST_CASE("SocketFactory can create valid RawSocket", "[SocketFactory]") {
    SysMock mock;
    mock.socket_ret = 1;
#ifndef SOCK_CLOEXEC
    mock.fcntl_getfd_ret = 0;
    mock.fcntl_setfd_ret = 0;
#endif

    SocketFactory<SysMock> factory(mock);
    auto rs = factory.create_tcp();
    REQUIRE(rs.native_handle() == 1);
}

