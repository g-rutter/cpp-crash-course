#include "fib.h"

bool FibonacciIterator::operator!=(int x) const {
    return x >= current;
}
FibonacciIterator& FibonacciIterator::operator++() {
    const auto tmp = current;
    current += last;
    last = tmp;
    return *this;
}
int FibonacciIterator::operator*() const {
    return current;
}

FibonacciRange::FibonacciRange(const int max) : max{ max } { }
FibonacciIterator FibonacciRange::begin() const {
    return FibonacciIterator{};
}
int FibonacciRange::end() const {
    return max;
}