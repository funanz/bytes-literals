# Byte array literals

## Requires
C++20

## Example
Generate a constant std::array
```C++
#include "bytes_literals.hpp"
using namespace bytes_literals;

constexpr auto a = 0x01234567_bytes; // a is std::array<uint8_t, 4>
```

Signed array use '\_sbytes'
```C++
constexpr auto a = 0x01234567_sbytes; // a is std::array<int8_t, 4>
```

Digit separator
```C++
constexpr auto a = 0x00010203'04050607'08090a0b'0c0d0e0f_bytes
```

From a hex string (Digit separator cannot be used)
```C++
constexpr auto c = to_bytes("01234567"); // c is std::array<uint8_t, 4>
constexpr auto d = to_sbytes("01234567"); // b is std::array<int8_t, 4>
```

Long array example
```C++
static constexpr auto sbox = to_bytes(
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
```

Code example
```C++
constexpr auto key = 0x000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f_bytes;
constexpr aes256 aes(key);
constexpr auto text = 0x00112233445566778899aabbccddeeff_bytes;
constexpr auto enc = aes.encrypt(text);
static_assert(enc == 0x8ea2b7ca516745bfeafc49904b496089_bytes);
constexpr auto dec = aes.decrypt(enc);
static_assert(dec == text);
```
