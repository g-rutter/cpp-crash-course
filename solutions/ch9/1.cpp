// Implement a fold function template with the following prototype: (see code - Gil)
// For example, your implementation must support the following usage: (see main function - Gil)
// The value of sum should be 1,500. Use fold to calculate the following quanti-
// ties: the maximum, the minimum, and the number of elements greater than 200.
#include <cstdio>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial){
    Out output{initial};
    for(int i=0; i<length; i++) output = function(output, input[i]);
    return output;
}

int main() {
    int data[]{ 100, 200, 300, 400, 500 };
    int floor{200};
    size_t data_len = 5;
    auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
    auto min = fold([](auto x, auto y) { return x < y ? x : y; }, &data[1], data_len - 1, data[0]);
    auto max = fold([](auto x, auto y) { return x > y ? x : y; }, &data[1], data_len - 1, data[0]);
    int n_greater = fold([floor](auto x, auto y) {return y > floor? ++x : x;}, data, data_len, 0);

    printf("Sum: %d\n", sum); // Should be: 1500. Is: 1500
    printf("Min: %d\n", min); // Should be: 100. Is: 0
    printf("Max: %d\n", max); // Should be: 500. Is: 500
    printf("N greater: %d\n", n_greater); // Should be: 3. Is: 3
}
