#include <iostream>
#include <utility>
#include <sys/time.h>

struct TimerClass {
    timeval timestamp;
    const char* name;
    bool moved_from = false;

    TimerClass (const char* name): name{name} {
        gettimeofday(&timestamp,NULL);
    }

    TimerClass (const TimerClass& other): timestamp{other.timestamp}, name{other.name}{}
    TimerClass& operator=(const TimerClass& other) {
        timestamp = other.timestamp;
        name = other.name;
        return *this;
    }

    TimerClass (TimerClass&& other) noexcept: timestamp{other.timestamp}, name{other.name}{
        other.moved_from = true;
    }
    TimerClass& operator=(TimerClass&& other) noexcept {
        timestamp = other.timestamp;
        name = other.name;
        other.moved_from = true;
        return *this;
    }

    ~TimerClass () {
        timeval end_timestamp, diff_timestamp;
        gettimeofday(&end_timestamp,NULL);
        timersub(&end_timestamp, &timestamp, &diff_timestamp);
        
        if (!moved_from) {
            printf("[%s]time=%ld.%06d s\n", name, diff_timestamp.tv_sec, diff_timestamp.tv_usec);
        }
    }
};

int main() {
    auto timerclass{TimerClass("original")};
    TimerClass timerclass_copy_cons{timerclass};

    TimerClass timerclass_copy_assign{"copy_assign"};
    timerclass_copy_assign = timerclass;

    TimerClass timerclass_move_cons{std::move(timerclass)};

    TimerClass timerclass_move_assign{"move_assign"};
    timerclass_move_assign = std::move(timerclass_move_cons);
    printf("Yowwww\n");
}