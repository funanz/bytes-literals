// The MIT License
// Copyright 2023 funanz <granz.fisherman@gmail.com>
// https://opensource.org/licenses/MIT

#include <cassert>
#include <cstdint>
#include <cstring>
#include "bytes_literals.hpp"

using namespace bytes_literals;

void test_bytes_literal()
{
    constexpr auto a = 0x00112233445566778899aabbccddeeff_bytes;
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0x7] == 0x77);
    static_assert(a[0xf] == 0xff);
}

void test_bytes_literal_separator()
{
    constexpr auto a = 0x00112233'44556677'8899aabb'ccddeeff_bytes;
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0x7] == 0x77);
    static_assert(a[0xf] == 0xff);
}

void test_bytes_literal_uppercase()
{
    constexpr auto a = 0X00112233445566778899AABBCCDDEEFF_bytes;
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0xa] == 0xaa);
    static_assert(a[0xf] == 0xff);
}

void test_bytes_literal_uppercase_separator()
{
    constexpr auto a = 0X00112233'44556677'8899AABB'CCDDEEFF_bytes;
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0xa] == 0xaa);
    static_assert(a[0xf] == 0xff);
}

void test_sbytes_literal()
{
    constexpr auto a = 0x007f80ff_sbytes;
    static_assert(a.size() == 4);
    static_assert(a[0] == 0);
    static_assert(a[1] == 127);
    static_assert(a[2] == -128);
    static_assert(a[3] == -1);
}

void test_string_to_bytes()
{
    constexpr auto a = to_bytes("00112233445566778899aabbccddeeff");
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0x7] == 0x77);
    static_assert(a[0xf] == 0xff);
}

void test_string_to_bytes_uppercase()
{
    constexpr auto a = to_bytes("00112233445566778899AABBCCDDEEFF");
    static_assert(a.size() == 16);
    static_assert(a[0x0] == 0x00);
    static_assert(a[0xa] == 0xaa);
    static_assert(a[0xf] == 0xff);
}

void test_string_to_sbytes()
{
    constexpr auto a = to_sbytes("007f80ff");
    static_assert(a.size() == 4);
    static_assert(a[0] == 0);
    static_assert(a[1] == 127);
    static_assert(a[2] == -128);
    static_assert(a[3] == -1);
}

void test_string_to_bytes_zero()
{
    constexpr auto a = to_bytes("");
    static_assert(a.size() == 0);
}

void test_string_to_bytes_long()
{
    static constexpr auto a = to_bytes(
        "637c777bf26b6fc53001672bfed7ab76"
        "ca82c97dfa5947f0add4a2af9ca472c0"
        "b7fd9326363ff7cc34a5e5f171d83115"
        "04c723c31896059a071280e2eb27b275"
        "09832c1a1b6e5aa0523bd6b329e32f84"
        "53d100ed20fcb15b6acbbe394a4c58cf"
        "d0efaafb434d338545f9027f503c9fa8"
        "51a3408f929d38f5bcb6da2110fff3d2"
        "cd0c13ec5f974417c4a77e3d645d1973"
        "60814fdc222a908846eeb814de5e0bdb"
        "e0323a0a4906245cc2d3ac629195e479"
        "e7c8376d8dd54ea96c56f4ea657aae08"
        "ba78252e1ca6b4c6e8dd741f4bbd8b8a"
        "703eb5664803f60e613557b986c11d9e"
        "e1f8981169d98e949b1e87e9ce5528df"
        "8ca1890dbfe6426841992d0fb054bb16"
        );
    static_assert(a.size() == 256);
    static_assert(a[0x00] == 0x63);
    static_assert(a[0x30] == 0x04);
    static_assert(a[0x88] == 0xc4);
    static_assert(a[0xff] == 0x16);
}

void test_string_to_bytes_invalid_prefix()
{
    try {
        (void)to_bytes("0x00");
    }
    catch (std::invalid_argument&) {}
}

void test_string_to_bytes_invalid_separator()
{
    try {
        (void)to_bytes("0'00");
    }
    catch (std::invalid_argument&) {}
}

void test_hex_to_bytes_short_input()
{
    constexpr auto s = "1234";
    std::uint8_t a[4] = { 0xff, 0xff, 0xff, 0xff };
    impl::hex_to_bytes(s, s + std::strlen(s), a, a + sizeof(a), false);
    assert(a[0] == 0x12);
    assert(a[1] == 0x34);
    assert(a[2] == 0xff);
    assert(a[3] == 0xff);
}

void test_hex_to_bytes_short_output()
{
    constexpr auto s = "12345678";
    std::uint8_t a[4] = { 0xff, 0xff, 0xff, 0xff };
    impl::hex_to_bytes(s, s + std::strlen(s), a, a + 1, false);
    assert(a[0] == 0x12);
    assert(a[1] == 0xff);
    assert(a[2] == 0xff);
    assert(a[3] == 0xff);
}

void test_hex_to_bytes_missing_low_byte()
{
    constexpr auto s = "123";
    std::uint8_t a[4] = { 0xff, 0xff, 0xff, 0xff };
    impl::hex_to_bytes(s, s + std::strlen(s), a, a + sizeof(a), false);
    assert(a[0] == 0x12);
    assert(a[1] == 0x30);
    assert(a[2] == 0xff);
    assert(a[3] == 0xff);
}

int main()
{
    test_bytes_literal();
    test_bytes_literal_separator();
    test_bytes_literal_uppercase();
    test_bytes_literal_uppercase_separator();
    test_sbytes_literal();
    test_string_to_bytes();
    test_string_to_bytes_uppercase();
    test_string_to_sbytes();
    test_string_to_bytes_zero();
    test_string_to_bytes_long();
    test_string_to_bytes_invalid_prefix();
    test_string_to_bytes_invalid_separator();
    test_hex_to_bytes_short_input();
    test_hex_to_bytes_short_output();
    test_hex_to_bytes_missing_low_byte();
}
