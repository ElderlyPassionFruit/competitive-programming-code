#include <bits/stdc++.h>

using namespace std;
#define int long long
map<int, int> mem;

int get(int x) {
    if (x <= 2) return 1;
    if (mem.count(x)) return mem[x];
    return mem[x] = get(x - 1) + get(x - 2) + get(x - 3);
}

signed main() {
    int x;
    cin >> x;
    cout << get(x);
    return 0;
}