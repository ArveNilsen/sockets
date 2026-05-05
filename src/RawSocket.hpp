#pragma once

#include <system_error>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <type_traits>

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

    native_handle_type fd_{ - 1 };
};

static_assert(std::is_standard_layout_v<RawSocket>);
