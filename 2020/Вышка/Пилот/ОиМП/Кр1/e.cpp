#include <vector>

template <typename T>
void Duplicate(std::vector<T>& v) {
    v.reserve(v.size() * 2);
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        v.push_back(*it);
    }
}

#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4};
    Duplicate(v);
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}