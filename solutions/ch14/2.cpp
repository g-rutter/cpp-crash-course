// EXERCISES
// 14-2. Write a function template called sum that accepts a half-open range of
//       int objects and returns the sum of the sequence.
#include <iterator>
#include <vector>

template<typename InputIterator>
using IteratorRtn = typename std::iterator_traits<InputIterator>::value_type;

template<typename InputIterator>
IteratorRtn<InputIterator> range_sum(InputIterator itr1, InputIterator itr2){
    IteratorRtn<InputIterator> result = 0;
    do {
        result += *itr1++;
    } while (itr1 != itr2);
    return result;
}

int main () {
    std::vector<int> stuff{1,-1,2,2,-3,-3};
    int result = range_sum(stuff.begin(), stuff.end());
    printf("Result: %d\n", result);
}
