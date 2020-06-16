// EXERCISES
// 15-2. Implement a program that determines whether the user’s input is a palindrome.
// 15-3. Implement a program that counts the number of vowels in the user’s input.
#include <cstdio>
#include <string_view>
#include <string>

bool is_palindrome(std::string_view input){
    auto forward_iter = input.begin();
    auto backward_iter = input.rbegin();
    unsigned int n_checks = input.length() / 2;
    while(n_checks--){
        if (*forward_iter != *backward_iter) return false;
        forward_iter++;
        backward_iter++;
    }
    return true;
}

unsigned int count_vowels(std::string_view input){
    const static std::string vowels = "aeiou";
    size_t starting_pos = 0;
    size_t found_at;
    unsigned int n_found{};
    do {
        found_at = input.find_first_of(vowels, starting_pos);
        starting_pos = found_at + 1;
        n_found++;
    } while (found_at < input.length());
    return n_found - 1; // End of string will always be found.
}

int main(int argc, char const *argv[])
{
    if(argc != 2) printf("Please pass one argument.");
    else {
        bool result = is_palindrome(argv[1]);
        auto n_vowels = count_vowels(argv[1]);
        printf("Is palindrome? %s\n", result ? "true" : "false");
        printf("Has %d vowels\n", n_vowels);
    }
}