#include <algorithm>
#include <deque>

void RemoveDuplicates(std::deque<int>& data) {
    data.resize(std::unique(data.begin(), data.end()) - data.begin());
}

#include <bits/stdc++.h>

using namespace std;

int main() {
    deque<int> a;
    for (int i = 0; i < 5000; ++i) {
        a.push_back(i);
        a.push_back(i);
        a.push_back(i);
    }
    RemoveDuplicates(a);
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}