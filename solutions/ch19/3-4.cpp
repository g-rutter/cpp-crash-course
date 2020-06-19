// 19-3. Create a thread-safe queue class. This class must expose an interface
//       like std::queue (see [queue.defn]). Use a std::queue internally to
//       store elements. Use a std::mutex to synchronize access to this
//       internal std::queue.
// 19-4. Add a wait_and_pop method and a std::condition_variable member to 
//       your thread-safe queue. When a user invokes wait_and_pop and the
//       queue contains an element, it should pop the element off the queue
//       and return it. If the queue is empty, the thread should block until
//       an element becomes available and then proceed to pop an element.
