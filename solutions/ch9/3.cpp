// 9-3. Implement an all function with the following prototype: (see code)
//      The Fn function type is a predicate that supports bool operator()(In).
//      Your all function must test whether function returns true for every element
//      of input. If it does, return true. Otherwise, return false.
//      For example, your implementation must support the following usage: (see main)
#include <cstdio>

template <typename Fn, typename In>
constexpr auto all(Fn function, In* input, size_t length){
    if (!length) return true;
    return function(input[0]) && all(function, &input[1], length-1);
}

int main() {
    int data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = 5;
    bool all_gt100 = all([](auto x) { return x > 100; }, data, data_len);
    if(all_gt100) printf("All elements greater than 100.\n");
}
