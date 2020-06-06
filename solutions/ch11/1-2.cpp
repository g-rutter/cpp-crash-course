// 11-1. Reimplement Listing 11-12 to use a std::shared_ptr rather than a std::unique_ptr.
//       Notice that although you’ve relaxed the ownership requirements from exclusive
//       to non-exclusive, you’re still transferring ownership to the say_hello function.
// 11-2. Remove the std::move from the call to say_hello. Then make an additional call to
//       say_hello. Notice that the ownership of file_guard is no longer transferred to
//       say_hello. This permits multiple calls.
#include <cstdio>
#include <memory>
#include <cerrno>

using FileGuard = std::shared_ptr<FILE>;

void say_hello(FileGuard file) {
    fprintf(file.get(), "HELLO DAVE\n");
}

int main() {
    auto file = fopen("HAL9000", "w");
    if (!file) return errno;
    const FileGuard file_guard{ file, fclose };
    // File open here
    say_hello(file_guard);
    say_hello(file_guard);
    // say_hello(std::move(file_guard));
    // File closed here
    return 0;
}