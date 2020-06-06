// EXERCISES
// 12-1. Reimplement the narrow_cast in Listing 6-6 to return a std::optional.
//       If the cast would result in a narrowing conversion, return an empty
//       optional rather than throwing an exception. Write a unit test that
//       ensures your solution works.
#include <stdexcept>
#include <optional>

template <typename To , typename From>
std::optional<To> narrow_cast(const From value) {
    const auto converted = static_cast<To>(value);
    const auto backwards = static_cast<From>(converted);
    if (value != backwards) return std::nullopt;
    return converted;
}

int main() {
    const double from{2.3456789};
    const std::optional<int> to{narrow_cast<int, double>(from)};
    if (to == std::nullopt) printf("Narrowing occurred\n");
}