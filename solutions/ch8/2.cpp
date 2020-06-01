//  8-2. Implement a PrimeNumberRange class that can be used in a range exception to
//       iterate over all prime numbers less than a given value. Again, use a separate
//       header and source file.
#include<cstdio>
#include "2.h"

bool PrimeNumberIterator::operator!=(const int x) {
    return x >= current;
}
int PrimeNumberIterator::operator*(){
    return current;
}
PrimeNumberIterator& PrimeNumberIterator::operator++() {
    bool found_prime{false};
    double int_div;
    double double_div;
    while (!found_prime) {
        current++;
        for(int i=2; i < current; i++) {
            int_div = double(current / i);
            double_div = double(current)/double(i);
            if(int_div == double_div) break; // Found a divisor; give up on this candidate early
            if(i + 1 == current) found_prime = true;
        }
    }
    return *this;
}

PrimeNumberRange::PrimeNumberRange(const int max): max{max} {}
PrimeNumberIterator PrimeNumberRange::begin() const {
    return PrimeNumberIterator{};
}
int PrimeNumberRange::end() const {
    return max;
}

int main(){
    for (const auto i : PrimeNumberRange{500}) {
        printf("%d\n", i);
    }
}