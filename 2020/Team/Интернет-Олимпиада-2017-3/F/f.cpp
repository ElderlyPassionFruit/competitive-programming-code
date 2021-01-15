#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Rect{
    int lx, ly, rx, ry;
    void read() {
        cin >> lx >> ly >> rx >> ry;
        lx--;
        ly--;
        rx--;
        ry--;
    }
};

const int N = 1e3 + 10;
int n, m, q;
Rect op[N];
int ans[N];
bool used[N][N];

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

struct Pt{
    int x, y;
    Pt() {}
    Pt(int _x, int _y) {
        x = _x, y = _y;
    }
};

bool operator==(const Pt& a, const Pt& b) {
    return tie(a.x, a.y) == tie(b.x, b.y);
}

struct Dsu{
    vector<vector<Pt>> p;
    int n, m;
    int comps;
    Dsu() {}
    Dsu(int _n, int _m) {
        n = _n, m = _m;
        comps = 0;
        p.assign(n, vector<Pt> (m, Pt(-1, -1)));
    }
    Pt getP(Pt v) {
        if (p[v.x][v.y] == v) {
            return v;
        }
        return p[v.x][v.y] = getP(p[v.x][v.y]);
    }
    void add(Pt a) {
        p[a.x][a.y] = a;
        ++comps;
    }
    void uni(Pt a, Pt b) {
        a = getP(a);
        b = getP(b);
        if (a == b) return;
        --comps;
        p[a.x][a.y] = b;
    }
};

Dsu dsu;

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void addPt(int x, int y) {
    used[x][y] = true;
    dsu.add({x, y});
    for (int it = 0; it < 4; ++it) {
        int nx = x + dx[it], ny = y + dy[it];
        if (!checkCell(nx, ny)) continue;
        if (!used[nx][ny]) continue;
        dsu.uni({x, y}, {nx, ny});
    }
}

int sum[N][N];

void make(int x, int y, int dx, int dy, int len, int add) {
    for (int i = 0; i < len; ++i) {
        sum[x][y] += add;
        if (sum[x][y] == 0) {
            addPt(x, y);
        }
        x += dx;
        y += dy;
    }
}

void make(Rect a, int add) {
    if (a.lx == a.rx && a.ly == a.ry) {
        make(a.lx, a.ly, 0, 0, 1, add);
    } else if (a.lx == a.rx) {
        make(a.lx, a.ly, 0, 1, a.ry - a.ly + 1, add);
    } else if (a.ly == a.ry) {
        make(a.lx, a.ly, 1, 0, a.rx - a.lx + 1, add);
    } else {
        make(a.lx, a.ly, 1, 0, a.rx - a.lx + 1, add);
        make(a.lx, a.ry, 1, 0, a.rx - a.lx + 1, add);
        make(a.lx, a.ly + 1, 0, 1, a.ry - a.ly - 1, add);
        make(a.rx, a.ly + 1, 0, 1, a.ry - a.ly - 1, add);
    }
}

void build() {
    dsu = Dsu(n, m);
    for (int i = 0; i < q; ++i) {
        make(op[i], 1);
    } 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (sum[i][j] == 0){
                addPt(i, j);
            }
        }
    }
   /* cout << "sum = " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }*/
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m >> q;
    for (int i = 0; i < q; ++i) {
        op[i].read();
    }
    build();
    for (int i = q - 1; i >= 0; --i) {
        ans[i] = dsu.comps;
        make(op[i], -1);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
	return 0;
}