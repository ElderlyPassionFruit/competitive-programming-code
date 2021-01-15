#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Point{
    int x, y;
};

int n;
string s;

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

int getDir(char x) {
    if (x == 'L') return 0;
    if (x == 'R') return 1;
    if (x == 'U') return 2;
    if (x == 'D') return 3;
    assert(false);
    return -1; 
}

void solve() {
    Point a;
    cin >> a.x >> a.y;
    for (auto i : s) {
        int dir = getDir(i);
        if (a.x + dx[dir] == 0 && a.y + dy[dir] == 0) continue;
        a.x += dx[dir];
        a.y += dy[dir];
    }
    cout << a.x << " " << a.y << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> s;
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}