// 12-2. Implement a program that generates random alphanumeric passwords and
//       writes them to the console. You can store the alphabet of possible
//       characters into a char[] and use the discrete uniform distribution with a
//       minimum of zero and a maximum of the last index of your alphabet array.
//       Use a cryptographically secure random number engine.
#include <cstdio>
#include <random>

int main() {
    constexpr int password_length{9};

    constexpr char letters[] = {'a', 'b', 'c', 'd', 'e', '!', 'p'};
    constexpr int n_choices{sizeof(letters)};
    
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0,n_choices-1);

    printf("Your password is:\n");
    for (size_t i = 0; i < password_length; i++) printf("%c", letters[distribution(generator)]);
    printf("\n");
}