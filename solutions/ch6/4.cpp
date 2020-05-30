// EXERCISES
// 6-4. Refactor mean in Listing 6-13 to accept an array rather than pointer and
//      length arguments. Use Listing 6-33 as a guide.
#include <cstddef>
#include <cstdio>

template<typename T, size_t Length>
T mean(const T (&arr)[Length]) {
    T result{};
    for(size_t i{}; i<Length; i++) result += arr[i];
    return result / Length;
}

int main() {
    const double nums_d[] { 1.0, 2.0, 3.0, 4.0 };
    const double result1 = mean(nums_d);
    printf("double: %f\n", result1);

    const float nums_f[] { 1.0f, 2.0f, 3.0f, 4.0f };
    const float result2 = mean(nums_f);
    printf("float: %f\n", result2);
    
    const size_t nums_c[] { 1, 2, 3, 4 };
    const size_t result3 = mean(nums_c);
    printf("size_t: %zd\n", result3);
}
