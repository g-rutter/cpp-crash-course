// 13-5. Consider the following program that profiles the performance of a function
//       summing a Fibonacci series: (below)
//       [...] Adapt your code from Exercise 13-1 by (a) generating the appropriate 
//       vector and (b) summing over the result with a range-based for loop. 
//       [...] Compile the program and run it a few times to get an idea of how long
//       your program takes to run. (This is called a baseline.)
// 13-6. Implement the function cached_fib_sum so you first check whether you’ve
//       computed fib_sum for the given length yet. (Treat the length n as a key
//       into the cache.) If the key is present in the cache, simply return the result.
//       If the key isn’t present, compute the correct answer with fib_sum, store the
//       new key-value entry into cache, and return the result. Run the program again.
//       Is it faster? Try unordered_map instead of map. Could you use a vector instead?
#include <chrono>
#include <cstdio>
#include <random>
#include <unordered_map>
#include <array>

long fib_sum(size_t n) {
    // Typical performance (direct usage): Elapsed: 1.73765 s.
    if(n < 3) return n;

    std::vector<unsigned long> vec;
    vec.reserve(n);
    vec.assign({1, 1});
    unsigned long sum{0};
    for (size_t i = vec.size(); i < 20; i++) vec.push_back(vec.at(i - 1) + vec.at(i - 2));
    for (auto &&i : vec) sum += i;
    return sum;
}

long random() {
    static std::mt19937_64 mt_engine{ 102787 };
    static std::uniform_int_distribution<long> int_d{ 1000, 2000 };
    return int_d(mt_engine);
}

struct Stopwatch {
    Stopwatch(std::chrono::nanoseconds& result)
        : result{ result },
          start{ std::chrono::system_clock::now() } { }
    ~Stopwatch() {
        result = std::chrono::system_clock::now() - start;
    }
    private:
        std::chrono::nanoseconds& result;
        const std::chrono::time_point<std::chrono::system_clock> start;
};

long cached_fib_sum_unordered_map(const size_t& n) {
    // Typical performance: Elapsed: 0.288716 s. 
    static std::unordered_map<size_t, unsigned long> cache;
    if(!cache.count(n)) cache[n] = fib_sum(n);
    return cache[n];
}

long cached_fib_sum_array(const size_t& n) {
    // Hard assumption that values will be on [1000, 2000]
    // No exception raising, risky in the wild.
    // Typical performance: Elapsed: 0.110766 s.
    static std::array<unsigned long, 1001> cache;
    if(!cache[n - 1000]) cache[n - 1000] = fib_sum(n - 1000);
    return cache[n - 1000];
}

int main() {
    size_t samples{ 1'000'000 };
    std::chrono::nanoseconds elapsed;
    {
        Stopwatch stopwatch{elapsed};
        volatile double answer;
        while(samples--) {
            // answer = fib_sum(random());
            answer = cached_fib_sum_array(random());
        }
    }
    printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000'000.);
}