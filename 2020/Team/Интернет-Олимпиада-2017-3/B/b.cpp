#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Fenwick{
    int n;
    vector<int> tree;
    Fenwick() {}
    Fenwick(int _n) {
        n = _n;
        tree.assign(n, 0);
    }
    void upd(int pos, int val) {
        for (; pos < n; pos |= pos + 1)
            tree[pos] += val;
    }
    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            ans += tree[r];
        }
        return ans;
    }
    int get(int l, int r) {
        if (l > r) swap(l, r);
        return get(r) - get(l - 1);
    }
};

const int N = 1e3 + 10;
int n, m, q;
char a[N][N];
Fenwick r[N], c[N];

void updVal(int x, int y, int add) {
    if (add == -1) {
        a[x][y] = '0';
    } else {
        a[x][y] = '1';
    }
    r[x].upd(y, add);
    c[y].upd(x, add);
}

void build() {
    for (int i = 0; i < n; i++) {
        r[i] = Fenwick(m);
    }
    for (int j = 0; j < m; j++) {
        c[j] = Fenwick(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') {
                updVal(i, j, 1);
            }
        }
    }
}

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

void upd(int x, int y, int dir) {
    if (a[x][y] == '0') return;
    int l = 0, r1 = max(n, m);
    while (l < r1 - 1) {
        int mid = (l + r1) / 2;
        int nx = x + dx[dir] * mid;
        int ny = y + dy[dir] * mid;
        if (!checkCell(nx, ny)) {
            r1 = mid;
            continue;
        }
        bool ok = true;
        if (x == nx) {
            if (r[x].get(y, ny) != abs(y - ny) + 1) {
                ok = false;
            }
        } else {
            if (c[y].get(x, nx) != abs(x - nx) + 1) {
                ok = false;
            }
        }
        if (ok) {
            l = mid;
        } else {
            r1 = mid;
        }
    }
    int nx = x + dx[dir] * r1;
    int ny = y + dy[dir] * r1;
    //cout << x << " " << y << " " << nx << " " << ny << endl;
    if (!checkCell(nx, ny)) return;
    updVal(x, y, -1);
    updVal(nx, ny, 1);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    build();
    while (q--) {
        int x, y, dir;
        cin >> x >> y >> dir;
        dir--;
        upd(x, y, dir);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << "\n";
    }
	return 0;
}
