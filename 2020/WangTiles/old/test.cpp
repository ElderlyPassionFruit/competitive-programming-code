
#include <iostream>

int main() {
    int* a = nullptr;
    if (!a) {
        a = new int;
    }
    *a = 5;
    std::cout << *a;
    delete a;
}