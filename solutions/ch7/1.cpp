// 7-1. Create an UnsignedBigInteger class that can handle numbers bigger than a long.
//      You can use a byte array as the internal representation (for example, uint8_t[] or char[]).
//      Implement operator overloads for operator+ and operator-. Perform runtime checks for overflow.
//      For the intrepid, also implement operator*, operator/, and operator%. Make sure that your
//      operator overloads work for both int types and UnsignedBigInteger types. Implement an
//      operator int type conversion. Perform a runtime check if narrowing would occur.
#include <cstdio>
#include <stddef.h>

template<int size>
struct UnsignedBigInteger {
    UnsignedBigInteger(const bool bits[size]) : bits{bits} {};
    UnsignedBigInteger() : bits{0} {};

    void printf_binary() {
        for (size_t i = 0; i < size; i++) printf("%d", bits[i]);
        printf("\n");
    }

    UnsignedBigInteger operator+(const UnsignedBigInteger other) const {
        bool carry{false};
        bool new_bits[size]{};
        for (size_t i = size - 1; i > 0; i--) {
            unsigned short total = bits[i] + other.bits[i] + carry;
            switch (total) {
                case 3:
                    new_bits[i] = true;
                    carry = true;
                    break;
                case 2:
                    new_bits[i] = false;
                    carry = true;
                    break;
                case 1:
                    new_bits[i] = true;
                    carry = false;
                    break;
                case 0:
                    new_bits[0] = false;
                    carry = false;
                    break;
            }
        }
        return UnsignedBigInteger{new_bits};

    }

    bool bits[size];
};

int main() {
    UnsignedBigInteger<100> big_int{};
    big_int.printf_binary();
    UnsignedBigInteger big_int2(big_int + big_int);
    big_int.printf_binary();
}