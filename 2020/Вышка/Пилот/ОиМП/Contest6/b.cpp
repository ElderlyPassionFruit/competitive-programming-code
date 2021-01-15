#include <algorithm>
#include <cstddef>

template<typename T>
class UniquePtr{
private:
    T* myPtr;

public:
    UniquePtr(UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr& other) = delete;

    UniquePtr() noexcept
        : myPtr(nullptr) {
    }

    UniquePtr(T* a) noexcept
       : myPtr(a) {
        a = nullptr;
    }

    UniquePtr(UniquePtr&& other) noexcept
        : myPtr(other.myPtr) {
        other.myPtr = nullptr;
    }

    UniquePtr& operator=(std::nullptr_t) noexcept {
        if (myPtr != nullptr) {
            delete myPtr;
            myPtr = nullptr;
        }
        return *this;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (myPtr != nullptr) {
            delete myPtr;
        }
        myPtr = other.myPtr;
        other.myPtr = nullptr;
        return *this;
    }

    T& operator*() const {
        return *myPtr;
    }

    T* operator->() const noexcept {
        return myPtr;
    }

    T* release() noexcept {
        T* ans = myPtr;
        myPtr = nullptr;
        return ans;
    }

    void reset(T* ptr) noexcept {
        *this = UniquePtr(ptr);
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(myPtr, other.myPtr);
    }

    T* get() const noexcept {
        return myPtr;
    }

    explicit operator bool() const noexcept {
        if (myPtr == nullptr) {
            return false;
        }
        return true;
    }

    ~UniquePtr() noexcept {
        if (myPtr != nullptr) {
            delete myPtr;
        }
    }
};

#include <bits/stdc++.h>
using namespace std;

int main() {
    int* a = new int(1);
    UniquePtr have(a);
    cout << (**have) << endl;
    have = nullptr;
    cout << (bool)(have) << endl;
}