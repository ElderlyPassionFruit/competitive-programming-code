#include <cassert>
#include <cstddef>

class Vector{
private:
    size_t sz;
    size_t ptr;
    int* data;

public:
    Vector()
        : sz(0)
        , ptr(0)
        , data(nullptr) {
    }

    Vector(const Vector& other)
        : sz(other.ptr)
        , ptr(other.ptr)
        , data(new int[other.ptr]) {
        for (size_t i = 0; i < ptr; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (data != nullptr) {
            delete[] data;
        }
        sz = other.ptr;
        ptr = other.ptr;
        data = new int[other.ptr];
        for (size_t i = 0; i < ptr; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    size_t size() const {
        return ptr;
    }

    int& operator[](size_t ind) const {
        assert(ind < ptr);
        return data[ind];
    }

    int& operator[](size_t ind) {
        assert(ind < ptr);
        return data[ind];
    }

    void push_back(int value) {
        if (ptr == sz) {
            if (sz == 0) {
                sz = 1;
                data = new int[sz];
            } else {
                int* lastValues = new int[ptr];
                for (size_t i = 0; i < ptr; ++i) {
                    lastValues[i] = data[i];
                }
                delete[] data;
                sz *= 2;
                data = new int[sz];
                for (size_t i = 0; i < ptr; ++i) {
                    data[i] = lastValues[i];
                }
                delete[] lastValues;
            }
        }
        data[ptr] = value;
        ++ptr;
    }

    void pop_back() {
        assert(ptr > 0);
        --ptr;
    }

    ~Vector() {
        if (data != nullptr) {
            delete[] data;
        }
    }
};

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(228);

int main() {
    Vector a;
    vector<int> fans;
    while (true) {
        int t = rnd() % 2;
        //int t = 0;
        if (fans.empty()) t = 0;
        if (t == 0) {
            int x = rnd();
            a.push_back(x);
            fans.push_back(x);
            cout << "push_back(x) = " << x << endl;
        } else {
            a.pop_back();
            fans.pop_back();
            cout << "pop_back()" << endl;
        }
        for (int i = 0; i < fans.size(); ++i) {
            assert(fans[i] == a[i]);
        }
        Vector b(a);
        for (int i = 0; i < fans.size(); ++i) {
            assert(fans[i] == b[i]);
        }
        
        //a = Vector(b);
        //Vector b = a;
        Vector c = a;
        Vector d = c;
        a = d;
    }
    return 0;
}