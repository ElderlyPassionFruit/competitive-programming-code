//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

using table = vector<vector<int>>;

int n, mxW;
table tiles;

void read() {
    cin >> n >> mxW;
    tiles.resize(n, vector<int> (4));
    for (auto& i : tiles) {
        for (auto& j : i) {
            cin >> j;
        }
    }
}

bool check(int i, int j, int it) {
    return tiles[i][it] == tiles[j][it ^ 2];
}

bool check(const table& tiles) {
    assert(!tiles.empty());
    for (int i = 0; i < tiles.size(); ++i) {
        if (!check(tiles[i][0], tiles[i].back(), 3)) {
            return false;
        }
    }
    for (int i = 0; i < tiles[0].size(); ++i) {
        if (!check(tiles[0][i], tiles.back()[i], 0)) {
            return false;
        }
    }
    return true;
}

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

bool checkCell(const table& a, int x, int y) {
    return x >= 0 && x < a.size() && y >= 0 && y < a[0].size();
}

bool checkAdd(const table& a, int x, int y, int i) {
    for (int it = 0; it < 4; ++it) {
        int nx = x + dx[it];
        int ny = y + dy[it];
        if (!checkCell(a, nx, ny)) continue;
        if (a[nx][ny] == -1) continue;
        if (!check(i, a[nx][ny], it)) {
            return false;
        }
    }
    return true;
}

const int N = 110;

vector<table> mem[N][N];

void wrMem() {
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            if (mem[i][j].empty()) continue;
            cout << "h = " << i << " w = " << j << " cnt = " << mem[i][j].size() << endl;
            /*for (auto x : mem[i][j]) {
                for (auto r : x) {
                    for (auto c : r) {
                        cout << c << " ";
                    }
                    cout << endl;
                }
                cout << endl;
        }*/
        }
    }
}

void relax(const table& now) {
    /*cout << "relax : now = " << endl;
    for (auto i : now) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    if (check(now)) {
        /*cout << "my answer : yes" << endl;
        for (auto i : now) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        //wrMem();
        */
        cout << now.size() << " " << now[0].size() << endl;
        //exit(0);
    }
    mem[now.size()][now[0].size()].push_back(now);
}

void solve(table& now, int x, int y) {
    
    if (x == -1) {
        relax(now);
        return;
    }

    int nx = x, ny = y;
    if (ny != now[0].size() - 1) {
        ny++;
    } else {
        nx--;
    }
    
    for (int i = 0; i < n; ++i) {
        if (!checkAdd(now, x, y, i)) {
            continue;
        }

        now[x][y] = i;
        solve(now, nx, ny);
        now[x][y] = -1;
    }
}

void Solve(const table& base, int n, int m) {
    table now = base;
    /*cout << "n = " << n << " m = " << m << " base = " << endl;
    for (auto i : base) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i <= n; ++i) {
        if (now.size() == i) now.push_back({});
        now[i].resize(m + 1, -1);
    }
    /*cout << "now = " << endl;
    for (auto i : now) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    solve(now, n, 0);
}

void run() {
    table myEmpty;
    for (int i = 0; i < N; ++i) {
        mem[i][0].push_back(myEmpty);
        if (i != 0) {
            mem[0][i].push_back(myEmpty);
        }
    }
    for (int w = 1; w <= mxW; ++w) {
        for (int h = 1; h <= w; ++h) {
            int sz = mem[w - 1][h - 1].size();
            for (const auto& lastTable : mem[w - 1][h - 1]) {
                Solve(lastTable, w - 1, h - 1);
            }
            assert(sz == mem[w - 1][h - 1].size());
        }
    }

    for (auto x : mem[4][1]) {
        //assert(!check(x));
        if (check(x)) {
            cout << "PUHH" << endl;
            for (auto i : x) {
                cout << "{";
                for (auto j : i) {
                    cout << "{";
                    cout << j << "},";
                }
                cout << "}";
            }
            cout << endl;
        }
        for (auto y : x) {
            for (auto z : y) {
                cout << z << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    if (mem[mxW][mxW].size()) {
        cerr << "puhh" << endl;
    }
}

void write() {
    //cout << "No" << endl;
    //wrMem();
    cout << "0 0\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}

/*

test 0

2 3
3 1 1 2
1 2 3 1

my answer : yes
0 1 
1 0 

*/