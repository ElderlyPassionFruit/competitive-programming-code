#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue{
private:
    Container myQueue;

public:
    Queue() {
        myQueue = {};
    }
    T front() const {
        return myQueue.front();
    }
    T& front() {
        return myQueue.front();
    }
    void pop() {
        myQueue.pop_front();
    }
    void push(const T& add) {
        myQueue.push_back(add);
    }
    Container getContainer() const {
        return myQueue;
    }
    size_t size() const {
        return myQueue.size();
    }
    bool empty() const {
        return myQueue.empty();
    }
    bool operator==(const Queue& a) const {
        return myQueue == a.getContainer();
    }
    bool operator!=(const Queue& a) const {
        return myQueue != a.getContainer();
    }
};