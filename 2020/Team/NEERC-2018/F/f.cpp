#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Figure{
    int x1, y1, x2, y2;
    Figure() {}
    Figure(int x, int y, int n) {
        x1 = x - n + 1, y1 = y - n + 1;
        x2 = x, y2 = y;
    }
    void print(int t) {
        if (t == 1 || t == 3) x1 = -x1, x2 = -x2;
        if (t == 2 || t == 3) y1 = -y1, y2 = -y2;
        cout << x2 << " " << y2 << " " << x1 << " " << y1 << '\n';
    }
};

void solve(int x, int y, int n, vector<Figure>& ans) {
    //cout << x << " " << y << " " << n << endl;
    if (x <= 0 && y <= 0) return;
    if (ans.empty()) {
        if (x < n && y < n) {
            ans.push_back({x, n - 1, n});
            return;
        } else if (y < n && x >= n) {
            ans.push_back({x, n - 1, n});
            x -= n - 1;
            y = 0;
        } else if (x < n && y >= n) {
            ans.push_back({x, y, n});
            x = 0;
            y -= n - 1;
        } else {
            ans.push_back({x, y, n});
            x -= n - 1;
            y -= n - 1;
        }
    } else {
        if (x >= n && y >= n) {
            if (x > y) {
                ans.push_back({x - 1, y, n});
                x--;
                x -= n - 1;
                y -= n - 1;
            } else {
                ans.push_back({x, y - 1, n});
                y--;
                x -= n - 1;
                y -= n - 1;
            }
        } else if (x < n && y >= n) {
            ans.push_back({x, y - 1, n});
            y--;
            x -= n - 1;
            y -= n - 1;
            x = 0;
        } else if (x >= n && y < n) {
            ans.push_back({x - 1, n - 1, n});
            x--;
            x -= n - 1;
            y = 0;
        } else {
            if (x == 0) {
                ans.push_back({x, y - 1, n});
                x = 0;
                y--;
                y -= n - 1;
            } else {
                ans.push_back({x - 1, n - 1, n});
                x -= n - 1;
                y = 0;
            }
            return;
        }
    }
    solve(x, y, n, ans);
}

/*
void print(Figure a, int t, int ind, vector<vector<char>>& out) {
    int x1 = a.x1;
    int x2 = a.x2;
    int y1 = a.y1;
    int y2 = a.y2;
    if (t == 1 || t == 3) x1 = -x1, x2 = -x2;
    if (t == 2 || t == 3) y1 = -y1, y2 = -y2;
    swap(x1, x2);
    swap(y1, y2);

    swap(x1, y1);
    swap(x2, y2);
    while (x2 != x1) {
        out[x1 + 10][y1 + 10] = '0' + ind;
        if (x2 > x1) ++x1;
        else --x1;
    }
    while (y2 != y1) {
        out[x1 + 10][y1 + 10] = '0' + ind;
        if (y2 > y1) ++y1;
        else --y1;
    }
    out[x1 + 10][y1 + 10] = '0' + ind;
}*/

void solve() {
    int n, x, y;
    cin >> x >> y >> n;
    int t;
    if (x >= 0 && y >= 0) {
        t = 0; 
    } else if (x < 0 && y >= 0) {
        t = 1;
    } else if (x >= 0 && y < 0) {
        t = 2;
    } else {
        assert(x < 0 && y < 0);
        t = 3;
    }
    x = abs(x);
    y = abs(y);
    vector<Figure> ans;
    solve(x, y, n, ans);
    cout << ans.size() << '\n';
    for (auto i : ans) {
        i.print(t);
    }
    /*vector<vector<char>> out(20, vector<char>(20, '.'));
    int it = 0;
    for (auto i : ans) {
        print(i, t, ++it, out);
    } 

    out[10][10] = 'x';
    for (int i = 19; i >= 0; --i) {
        for (auto j : out[i]) {
            cout << j;
        }
        cout << endl;
    }*/
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
	return 0;
}

// 6 8 3