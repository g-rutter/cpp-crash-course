// EXERCISES
// 19-1. Write your own spin lock-based mutex called SpinLock. Expose a lock,
//       a try_lock, and an unlock method. Your class should delete the copy
//       constructor. Try using a std::lock_guard<SpinLock> with an instance
//       of your class.
#include <mutex>
#include <iostream>
#include <future>
#include <atomic>
 

 struct SpinLock {
    SpinLock() {};
    SpinLock(SpinLock& other) = delete;
    SpinLock(SpinLock&& other) = delete;
    
    void lock() {
        while(locked.test_and_set(std::memory_order_acquire)) {};
    }

    bool try_lock() {
        if(locked.test_and_set(std::memory_order_acquire)) return false;
        return true;
    }

    void unlock() {
        locked.clear(std::memory_order_release);               
    }

    private:
       std::atomic_flag locked = ATOMIC_FLAG_INIT;
 };

void goat_rodeo() {
    const size_t iterations{ 1'000'000 };
    int tin_cans_available{};
    SpinLock tin_can_mutex;
    auto eat_cans = std::async(std::launch::async, [&] {
        for(size_t i{}; i<iterations; i++) {
            std::lock_guard<SpinLock> guard{ tin_can_mutex };
            tin_cans_available--;
        }
    });
    auto deposit_cans = std::async(std::launch::async, [&] {
        for(size_t i{}; i<iterations; i++) {
            std::lock_guard<SpinLock> guard{ tin_can_mutex };
            tin_cans_available++;
        }
    });
    eat_cans.get();
    deposit_cans.get();
    std::cout << "Tin cans: " << tin_cans_available << "\n";
}

int main() {
    goat_rodeo();
    goat_rodeo();
    goat_rodeo();
}