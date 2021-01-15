#include <bits/stdc++.h>

using namespace std;

#include <iostream>

size_t ar[] = {1, 2, 3, 4};
bool f(int a) {
    for (int i = 0; i <= 4; ++i)
        if (ar[i] == a)
            return true;
    return false;
}

int main() {
    std::cout << f(-2);
}