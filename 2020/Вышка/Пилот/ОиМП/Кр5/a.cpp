#include <iostream>
#include <memory>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

class B: {
private:
    A data1, data2;
public:
    B()
        : data1(42)
        , data2(17) {
    }
};

//#include "your_code.h"

int main() {
    std::unique_ptr<A> ptr = std::make_unique<B>();;
    ptr->foo();
}