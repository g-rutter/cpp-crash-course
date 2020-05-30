// EXERCISES
// 6-1. The mode of a series of values is the value that appears most commonly.
//      Implement a mode function using the following signature: int mode(const int* values, size_t length).
//      If you encounter an error condition, such as input having multiple modes and no values, return zero.
// 6-2. Implement mode as a template function.
// 6-3. Modify mode to accept an Integer concept. Verify that mode fails to
//      instantiate with floating types like double.
// 6-4. Refactor mean in Listing 6-13 to accept an array rather than pointer and
//      length arguments. Use Listing 6-33 as a guide.
// 6-5. Using the example from Chapter 5, make Bank a template class that accepts a template parameter.
//      Use this type parameter as the type of an account rather than long.
//      Verify that your code still works using a Bank<long> class.
// 6-6. Implement an Account class and instantiate a Bank<Account>. Implement functions in Account to keep track of balances.
// 6-7. Make Account an interface. Implement a CheckingAccount and SavingsAccount.
//      Create a program with several checking and savings accounts.
//      Use a Bank<Account> to make several transactions between the accounts.
#include <cstdio>
#include <unordered_map>
#include <type_traits>

template<typename T>
T mode(const T* values, size_t length){
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