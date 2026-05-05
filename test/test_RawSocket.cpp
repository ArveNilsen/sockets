#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#include <sockets/RawSocket.hpp>

TEST_CASE("RawSocket not default constructible", "[RawSocket]") {
    REQUIRE(std::is_default_constructible<RawSocket>::value == false);
}

TEST_CASE("RawSocket constructs from native handle", "[RawSocket]") {
    RawSocket rs(1);
    REQUIRE(rs.native_handle() == 1);
}

TEST_CASE("RawSocket no copy constructor", "[RawSocket]") {
    REQUIRE(std::is_copy_constructible<RawSocket>::value == false);
}

TEST_CASE("RawSocket no copy assignment", "[RawSocket]") {
    REQUIRE(std::is_copy_assignable<RawSocket>::value == false);
}

TEST_CASE("RawSocket is move constructible", "[RawSocket]") {
    REQUIRE(std::is_move_constructible<RawSocket>::value == true);
}

TEST_CASE("RawSocket is move assignable", "[RawSocket]") {
    REQUIRE(std::is_move_assignable<RawSocket>::value == true);
}

TEST_CASE("RawSocket can return native handle", "[RawSocket]") {
    RawSocket s(2);
    REQUIRE(s.native_handle() == 2);
}

TEST_CASE("RawSocket can release its fd", "[RawSocket]") {
    RawSocket s(2);
    REQUIRE(s.native_handle() == 2);
    REQUIRE(s.release() == 2);
    REQUIRE(s.native_handle() == -1);
}

TEST_CASE("RawSocket is valid except for fd -1", "[RawSocket]") {
    RawSocket s1(1);
    REQUIRE(s1.valid());
    RawSocket s2(-1);
    REQUIRE(!s2.valid());
}

