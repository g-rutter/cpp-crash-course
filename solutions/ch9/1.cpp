// Implement a fold function template with the following prototype: (see code - Gil)
// For example, your implementation must support the following usage: (see main function - Gil)
// The value of sum should be 1,500. Use fold to calculate the following quanti-
// ties: the maximum, the minimum, and the number of elements greater than 200.
#include <cstdio>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial){
    Out output{initial};
    for(int i=0; i<length; i++){
        output = function(output, input[i]);
    }
    return output;
}

int main() {
    int data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = 5;
    auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
    printf("Sum: %d\n", sum); // Should be: 1500. Is: 1500
}