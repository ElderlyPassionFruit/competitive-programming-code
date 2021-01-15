#include <iostream>

class C {
private:
    static int counter;
    const int id;

public:
    C(): id(++counter) {
        std::cout << "constructor C() " << id << "\n";
    }

    C(const C& other): id(++counter) {
        std::cout << "constructor C(const C&) " << id << " " << other.id << "\n";
    }

    C(C&& other): id(++counter) {
        std::cout << "constructor C(const C&&) " << id << " " << other.id << "\n";
    }

    C& operator = (const C& other) {
        std::cout << "operator = (const C&) " << id << " " << other.id << "\n";
        return *this;
    }

    C& operator = (C&& other) {
        std::cout << "operator = (const C&&) " << id << " " << other.id << "\n";
        return *this;
    }

    ~C() {
        std::cout << "destructor C() " << id << "\n";
    }
};

int C::counter = 0;

//#include "c.h"
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<C*> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(new C);
    }
    for (int i = 0; i < n; ++i) {
        delete a.back();
        a.pop_back();
    }
    return 0;
}