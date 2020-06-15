// EXERCISES
// 14-2. Write a function template called sum that accepts a half-open range of
//       int objects and returns the sum of the sequence.
#include <iterator>
#include <vector>

template <typename A>
using InputIterator = typename std::vector<A>::iterator;

template<typename A>
A range_sum(InputIterator<A> itr1, InputIterator<A> itr2) {
    A result = 0;
    do {
        result += *itr1++;
    } while (itr1 != itr2);
    return result;
}

int main () {
    std::vector<int> stuff{1,1,2,2,3,3};
    int result = range_sum<int>(stuff.begin(), stuff.end());
    printf("Result: %d\n", result);
}