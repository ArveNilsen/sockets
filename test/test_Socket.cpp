#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#include "../src/Socket.hpp"

TEST_CASE("Socket default constructible", "[Socket]") {
    REQUIRE(std::is_default_constructible<Socket>::value == true);
}
