#include <deque>
#include <iostream>
#include <utility>

using namespace std;

void add(int position, int number, deque<pair<int, int>>& box) {
    while (!box.empty() && box.back().first >= number) {
        box.pop_back();
    }
    box.push_back({number, position});
}

void del(int position, deque<pair<int, int>>& box) {
    if (box.front().second == position) {
        box.pop_front();
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    deque<pair<int, int>> box;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        add(i, x, box);
    }
    cout << box.front().first << "\n";
    for (int i = k; i < n; ++i) {
        int x;
        cin >> x;
        add(i, x, box);
        del(i - k, box);
        cout << box.front().first << "\n";
    }
    return 0;
}
