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


template<typename A>
struct SafeQueue {
    SafeQueue() {};

    A front() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.front();
    }

    A back() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.back();
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }

    template<typename B>
    void push(B&& value){
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::forward<B>(value));
    }

    template< typename... Args >
    decltype(auto) emplace( Args&&... args ){
        std::lock_guard<std::mutex> lock(mutex);
        queue.emplace(std::forward<Args>(args)...);
    }

    void pop(){
        std::lock_guard<std::mutex> lock(mutex);
        queue.pop();
    }

    void swap( SafeQueue& other ) noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        std::swap(queue, other.queue);
    }

    private:
        std::queue<A> queue{};
        std::mutex mutex{};
};

int main() {
    SafeQueue<int> my_queue;

    int myint{2};
    my_queue.push(1);
    my_queue.push(myint);
    std::cout << "Number of elements: " << my_queue.size() << std::endl;
}