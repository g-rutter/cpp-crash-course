// 11-3. Implement a Hal class that accepts a std::shared_ptr<FILE> in its constructor.
//       In Hal’s destructor, write the phrase "Stop, Dave". to the file handle held by
//       your shared pointer. Implement a write_status function that writes the phrase
//       "I'm completely operational". to the file handle.
// 11-4. Create several Hal instances and invoke write_status on them. Notice that you
//       don’t need to keep track of how many Hal instances are open: file management gets
//       handled via the shared pointer’s shared ownership model.
#include <memory>
#include <cerrno>

using FileGuard = std::shared_ptr<FILE>;

struct Hal {
    Hal(const FileGuard file) : file{file} {}
    ~Hal(){
        fprintf(file.get(), "Stop, Dave\n");
    }
    void write_status() const {
        fprintf(file.get(), "I'm completely operational\n");
    }
    const FileGuard file;
};

int main() {
    const auto file = fopen("HAL9000", "w");
    if (!file) return errno;
    const FileGuard file_guard{ file, fclose };
    Hal(file_guard).write_status();
    Hal hal{file_guard};
    hal.write_status();
    Hal(file_guard).write_status();
}