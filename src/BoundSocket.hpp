#pragma once

#include <utility>
#include <sys/socket.h>
#include "RawSocket.hpp"
#include "SysPolicy.hpp"

struct BoundSocket {
    BoundSocket() = delete;
    explicit BoundSocket(RawSocket rs) noexcept : sock_(std::move(rs)) {}

    BoundSocket(const BoundSocket&) = delete;
    BoundSocket& operator=(const BoundSocket&) = delete;
    BoundSocket(BoundSocket&&) noexcept = default;
    BoundSocket& operator=(BoundSocket&&) noexcept = default;

    RawSocket::native_handle_type native_handle() const noexcept { 
        return sock_.native_handle(); 
    }
    RawSocket release_raw() noexcept { return std::move(sock_); }

    RawSocket sock_;
};

static_assert(std::is_standard_layout_v<BoundSocket>);

