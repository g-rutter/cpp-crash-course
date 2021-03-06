// 7-1. Create an UnsignedBigInteger class that can handle numbers bigger than a long.
//      You can use a byte array as the internal representation (for example, uint8_t[] or char[]).
//      Implement operator overloads for operator+ and operator-. Perform runtime checks for overflow.
//      For the intrepid, also implement operator*, operator/, and operator%. Make sure that your
//      operator overloads work for both int types and UnsignedBigInteger types. Implement an
//      operator int type conversion. Perform a runtime check if narrowing would occur.
#include <cstdio>
#include <iostream>
#include <stddef.h>
#include <stdexcept>
#include <type_traits>

template<int size>
struct UnsignedBigInteger {
    UnsignedBigInteger(const bool bits_input[size]) {
        for (size_t i = 0; i < size; i++) bits[i] = bits_input[i];
    };
    UnsignedBigInteger() : bits{0} {};

    UnsignedBigInteger(int value) {
        // TODO case of negative/signed number
        for (size_t i = size; i > 0; i--) {
            bits[i-1] = value % 2;
            value /= 2;
        }
        if (value > 0) throw std::overflow_error("Input too large to represent as UnsignedBigInteger");
    };

    void printf_binary() const {
        for (size_t i = 0; i < size; i++) printf("%d", bits[i]);
        printf("\n");
    }

    template<typename Integer>
    explicit operator Integer() const {
        static_assert(std::is_integral<Integer>::value, "Can't cast UnsignedBigInteger to non-integer type.");
        Integer rtn{};
        for (size_t i = size; i > 0; i--) rtn += bits[i-1] << (size - i);
        // TODO test overflow
        return rtn;
    }

    UnsignedBigInteger operator+(const UnsignedBigInteger& other) const {
        bool carry{false};
        bool new_bits[size]{};
        unsigned short total;
        for (size_t i = size; i > 0; i--) {
            total = bits[i-1] + other.bits[i-1] + carry;
            carry = total > 1;
            new_bits[i-1] = total % 2;
        }
        if(carry) throw std::overflow_error("Max size of UnsignedBigInteger reached during addition.");
        return UnsignedBigInteger{new_bits};
    }

    UnsignedBigInteger operator-(const UnsignedBigInteger& other) const {
        bool carry{false};
        bool new_bits[size]{};
        short total;
        for (size_t i = size; i > 0; i--) {
            total = bits[i-1] - other.bits[i-1] - carry;
            carry = total < 0;
            new_bits[i-1] = total % 2;
        }
        if(carry) throw std::underflow_error("Min size of UnsignedBigInteger reached during addition.");
        return UnsignedBigInteger{new_bits};
    }

    bool bits[size];
};

int main() {
    const UnsignedBigInteger<7> big_int{21};
    big_int.printf_binary(); // 0010101
    const UnsignedBigInteger big_int2(big_int + big_int);
    big_int2.printf_binary(); // 0101010

    const auto normal_int{static_cast<int>(big_int2)};
    printf("%d\n", normal_int); // 42

    const UnsignedBigInteger<7> big_int3{15};
    big_int3.printf_binary(); // 0001111
    const UnsignedBigInteger big_int4(big_int - big_int3);
    big_int4.printf_binary(); // 0000110
    const auto normal_int2{static_cast<int>(big_int4)};
    printf("%d\n", normal_int2); // 6
}