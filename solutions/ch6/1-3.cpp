// EXERCISES
// 6-1. The mode of a series of values is the value that appears most commonly.
//      Implement a mode function using the following signature: int mode(const int* values, size_t length).
//      If you encounter an error condition, such as input having multiple modes and no values, return zero.
// 6-2. Implement mode as a template function.
// 6-3. Modify mode to accept an Integer concept. Verify that mode fails to
//      instantiate with floating types like double.
#include <cstdio>
#include <unordered_map>
#include <type_traits>

template<typename T>
T mode(const T* values, const size_t length) {
    static_assert(std::is_integral<T>::value, "Pointer values must be integral type.");
    std::unordered_map<T, int> value_counts;
    for (size_t i = 0; i < length; i++) value_counts[values[i]]++;

    int count_max = 0;
    T arg_max = 0;

    for (std::pair<T, int> pair : value_counts){
        if (pair.second > count_max) {
            count_max = pair.second;
            arg_max = pair.first;
        }
    }

    return arg_max;
}

int main() {
    const int values[] = {1, 0, 2, 2};
    auto mode_ = mode(values, sizeof(values) / sizeof(values[0]));
    printf("%d", mode_);
    return 0;
}