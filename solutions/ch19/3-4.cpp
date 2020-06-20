// 19-3. Create a thread-safe queue class. This class must expose an interface
//       like std::queue (see [queue.defn]). Use a std::queue internally to
//       store elements. Use a std::mutex to synchronize access to this
//       internal std::queue.
// 19-4. Add a wait_and_pop method and a std::condition_variable member to 
//       your thread-safe queue. When a user invokes wait_and_pop and the
//       queue contains an element, it should pop the element off the queue
//       and return it. If the queue is empty, the thread should block until
//       an element becomes available and then proceed to pop an element.
#include <queue>
#include <mutex>
#include <iostream>
#include <future>

template<typename A>
struct SafeQueue {
    SafeQueue() {};

    A front() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.front();
    }

    A back() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.back();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }

    template<typename B>
    void push(B&& value){
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::forward<B>(value));
        cv.notify_one();
    }

    template< typename... Args >
    decltype(auto) emplace( Args&&... args ){
        std::lock_guard<std::mutex> lock(mutex);
        queue.emplace(std::forward<Args>(args)...);
        cv.notify_one();
    }

    void pop(){
        std::lock_guard<std::mutex> lock(mutex);
        return queue.pop();
    }

    void swap( SafeQueue& other ) noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        std::swap(queue, other.queue);
    }

    A wait_and_pop() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if(!queue.empty()) {
                A rtn = queue.back();
                queue.pop();
                return rtn;
            }
        }

        std::unique_lock<std::mutex> lk(mutex);
        cv.wait(lk, [&]{return !queue.empty();});
        const A rtn = queue.back();
        queue.pop();
        lk.unlock();
        return rtn;
    }

    private:
        std::queue<A> queue{};
        mutable std::mutex mutex{};
        std::condition_variable cv{};
};

int main() {
    SafeQueue<int> my_queue;

    auto get_last_value = std::async(std::launch::async, [&] { return my_queue.wait_and_pop(); });

    const int myint{27};
    my_queue.push(1);
    my_queue.push(myint);
    my_queue.emplace(myint);
    const int last_value = get_last_value.get();
    std::cout << "Number of elements: " << my_queue.size() << std::endl;
    std::cout << "Last value: " << last_value << std::endl;
}