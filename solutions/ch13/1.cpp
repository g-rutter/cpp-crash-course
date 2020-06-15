// EXERCISES
// 13-1. Write a program that default constructs a std::vector of unsigned longs.
//       Print the capacity of vector and then reserve 10 elements. Next, append
//       the first 20 elements of the Fibonacci series to the vector. Print
//       capacity again. Does capacity match the number of elements in the
//       vector? Why or why not? Print the elements of vector using a range-based
//       for loop.
#include <vector>

int main() {
    std::vector<unsigned long> vec;
    printf("Size: %lu\n", vec.size());
    printf("Capacity: %lu\n", vec.capacity());

    vec.reserve(10);
    vec.assign({1, 1});
    for (size_t i = vec.size(); i < 20; i++) vec.push_back(vec.at(i - 1) + vec.at(i - 2));
    printf("Capacity after: %lu\n", vec.capacity());

    for (auto &&i : vec) printf("%lu ", i);
    printf("\n");    
}