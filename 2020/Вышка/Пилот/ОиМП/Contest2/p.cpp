#include <algorithm>
#include <vector>

void delete_zeroes(std::vector<int>& numbers) {
    numbers.erase(std::remove(numbers.begin(), numbers.end(), 0), numbers.end());
}

#include <bits/stdc++.h>
#include <iostream>

std::mt19937 rnd(time(0));

int main() {
    int n = 1e6;
    std::vector<int> a(n, 0);
    for (int i = 0; i < n; i += rnd() % 10) {
        a[i] = 1;
    }
    delete_zeroes(a);
    
    std::cout << "puhh" << std::endl;
    return 0;
}