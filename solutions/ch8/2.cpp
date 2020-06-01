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
    bool is_prime{true};
    double int_div;
    double double_div;
    while (true) {
        is_prime = true;
        current++;
        for(int i=2; i < current; i++) {
            int_div = double(current / i);
            double_div = double(current)/double(i);
            if(int_div == double_div){
                is_prime = false;
                break;
            }
        }
        if(is_prime) break;
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