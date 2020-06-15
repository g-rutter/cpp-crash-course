// 13-2. Rewrite Listings 2-9, 2-10, and 2-11 in Chapter 2 using std::array.
#include <cstdio>
#include <array>

int main() {
    // Listing 2-9:
    std::array<int, 4> arr1{ 1, 2, 3, 4 };
    printf("The third element is %d.\n", arr1.at(2));
    arr1.at(2) = 100;
    printf("The third element is %d.\n", arr1.at(2));

    // Listing 2-10:
    unsigned long maximum = 0;
    std::array<unsigned long, 5> arr2{ 10, 50, 20, 40, 0 };
    for(size_t i=0; i < 5; i++) {
        if (arr2.at(i) > maximum) maximum = arr2.at(i);
    }
    printf("The maximum value is %lu.\n", maximum);

    // Listing 2-11
    unsigned long maximum2 = 0;
    for(unsigned long value : arr2) {
        if (value > maximum) maximum = value;
    }
    printf("The maximum value is %lu.\n", maximum);

}