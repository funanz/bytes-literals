#pragma once
#ifndef INCLUDED_BYTES_LITERALS
#define INCLUDED_BYTES_LITERALS
// The MIT License
// Copyright 2023 funanz <granz.fisherman@gmail.com>
// https://opensource.org/licenses/MIT

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace bytes_literals {
    namespace impl {
        constexpr std::uint8_t hex_to_num(char c)
        {
            if ('0' <= c && c <= '9')
                return c - '0';
            else if ('a' <= c && c <= 'f')
                return c - 'a' + 10;
            else if ('A' <= c && c <= 'F')
                return c - 'A' + 10;
            else
                throw std::invalid_argument("invalid hex character [0-9a-fA-F]");
        }

        template <class InIter, class OutIter>
        constexpr void hex_to_bytes(InIter s_first, InIter s_last,
                                    OutIter o_first, OutIter o_last,
                                    bool ignore_quote)
        {
            auto s = s_first;
            auto o = o_first;
            int high = 1;
            while (s != s_last && o != o_last) {
                auto c = *s++;
                if (ignore_quote && c == '\'') continue;

                auto n = hex_to_num(c);
                if (high)
                    *o = n << 4;
                else
                    *o++ |= n;
                high ^= 1;
            }
        }

        template <class Array, class InIter>
        constexpr auto hex_to_bytes(InIter first, InIter last, bool ignore_quote)
        {
            Array a;
            hex_to_bytes(first, last, a.begin(), a.end(), ignore_quote);
            return a;
        }

        template <class T, char...S>
        constexpr auto bytes_literal()
        {
            constexpr char s[] = { S... };
            static_assert(sizeof(s) > 2, "requires prefix '0x'");
            static_assert(s[0] == '0', "requires prefix '0x'");
            static_assert(s[1] == 'x' || s[1] == 'X', "requires prefix '0x'");

            constexpr std::size_t prefix = 2;
            constexpr std::size_t quotes = std::count(s, s + sizeof(s), '\'');
            constexpr std::size_t len = sizeof(s) - prefix - quotes;
            static_assert(len % 2 == 0, "missing low byte");

            using result_type = std::array<T, len / 2>;
            constexpr auto a = hex_to_bytes<result_type>(s + prefix, s + sizeof(s), true);
            return a;
        }

        template <class T, std::size_t N>
        constexpr auto to_bytes(const char (&s)[N])
        {
            constexpr auto len = N - 1;
            static_assert(len % 2 == 0, "missing low byte");

            using result_type = std::array<T, len / 2>;
            return hex_to_bytes<result_type>(s, s + len, false);
        }
    } // namespace impl

    template <char...S>
    [[nodiscard]]
    constexpr auto operator ""_bytes()
    {
        return impl::bytes_literal<std::uint8_t, S...>();
    }

    template <char...S>
    [[nodiscard]]
    constexpr auto operator ""_sbytes()
    {
        return impl::bytes_literal<std::int8_t, S...>();
    }

    template <std::size_t N>
    [[nodiscard]]
    constexpr auto to_bytes(const char (&s)[N])
    {
        return impl::to_bytes<std::uint8_t>(s);
    }

    template <std::size_t N>
    [[nodiscard]]
    constexpr auto to_sbytes(const char (&s)[N])
    {
        return impl::to_bytes<std::int8_t>(s);
    }
}

#endif
