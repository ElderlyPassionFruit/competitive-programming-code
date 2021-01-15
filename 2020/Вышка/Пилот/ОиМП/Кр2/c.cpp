#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    Deque() {
        head = {};
        tail = {};
    }

    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    void Clear() {
        head.clear();
        tail.clear();
    }

    const T& operator[](size_t i) const {
        return At(i);
    }

    T& operator[](size_t i) {
        return At(i);
    }

    // throws std::out_of_range on incorrect index
    const T& At(size_t i) const {
        if (i < 0 || i >= Size()) {
            throw std::out_of_range("incorrect index");
        }
        if (i < head.size()) {
            return head[head.size() - 1 - i];
        }
        i -= head.size();
        return tail[i];
    }

    // throws std::out_of_range on incorrect index
    T& At(size_t i) {
        if (i < 0 || i >= Size()) {
            throw std::out_of_range("incorrect index");
        }
        if (i < head.size()) {
            return head[head.size() - 1 - i];
        }
        i -= head.size();
        return tail[i];
    }

    const T& Front() const {
        return At(0);
    }

    T& Front() {
        return At(0);
    }

    const T& Back() const {
        return At(Size() - 1);
    }

    T& Back() {
        return At(Size() - 1);
    }

    void PushFront(const T& elem) {
        head.push_back(elem);
    }

    void PushBack(const T& elem) {
        tail.push_back(elem);
    }
};