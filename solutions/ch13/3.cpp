// 13-3. Write a program that accepts any number of command line arguments
//       and prints them in alphanumerically sorted order. Use a
//       std::set<const char*> to store the elements, then iterate over
//       the set to obtain the sorted result. You’ll need to implement a
//       custom comparator that compares two C-style strings.
#include <set>

struct CStringComparator{
    bool operator()(const char* a, const char* b) const {
        size_t max_index = std::min(strlen(a), strlen(b));
        for (size_t i = 0; i < max_index; i++)
        {
            if (a[i] < b[i]) return true;
            else if (a[i] > b[i]) return false;
        }
        return strlen(a) < strlen(b);
    }
};

int main(int argc, char const *argv[])
{
    std::set<const char*, CStringComparator> arguments(argv + 1, argv + argc);
    for (const char* str : arguments) printf("%s\n", str);
    return 0;
}
