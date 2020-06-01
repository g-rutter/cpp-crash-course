// EXERCISES
// 8-1. Refactor Listing 8-27 into separate translation units: one for main and another for
//      FibonacciRange and FibonacciIterator. Use a header file to share definitions between the two translation units.
// 8-2. Implement a PrimeNumberRange class that can be used in a range exception to iterate over all prime numbers
//      less than a given value. Again, use a separate header and source file.
// 8-3. Integrate PrimeNumberRange into Listing 8-27, adding another loop that generates all prime numbers less than 5,000.
#include <cstdio>
#include "fib.h"

int main() {
    for (const auto i : FibonacciRange{ 5000 }) printf("%d ", i);
    printf("\n");
}