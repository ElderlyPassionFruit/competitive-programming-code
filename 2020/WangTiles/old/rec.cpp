#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()
#define sample sample228

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

using table = vector<vector<int>>;

namespace Solver{
    int n, mxW;
    table tiles;

    const int N = 110;
    vector<table> mem[N][N];

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

    /*
    void wrMem() {
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < N; ++j) {
                if (mem[i][j].empty()) continue;
                cout << "h = " << i << " w = " << j << " cnt = " << mem[i][j].size() << endl;
                for (auto x : mem[i][j]) {
                    for (auto r : x) {
                        for (auto c : r) {
                            cout << c << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
            }
        }
    }*/

    bool flag;

    table ansTalbe;

    void relax(const table& now) {
        /*cout << "relax : now = " << endl;
        for (auto i : now) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }*/
        if (check(now)) {
            if (min(now.size(), now[now.size() - 1].size()) == 11) {
                cout << "found!" << endl;
                cout << now.size() << " " << now[now.size() - 1].size() << endl;
                for (auto i : now) {
                    for (auto j : i) {
                        cout << j << " ";
                    }
                    cout << endl;
                }
                cout << "tiles = " << endl;
                for (auto i : tiles) {
                    for (auto j : i) {
                        cout << j << " ";
                    }
                    cout << endl;
                }
            }
            flag = true;
            ansTalbe = now;
            return;
            /*cout << "my answer : yes" << endl;
            for (auto i : now) {
                for (auto j : i) {
                    cout << j << " ";
                }
                cout << endl;
            }
            //wrMem();
            */
            /*cout << now.size() << " " << now[0].size() << endl;
            exit(0);*/
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
        for (int i = 0; i <= n; ++i) {
            if (now.size() == i) now.push_back({});
            now[i].resize(m + 1, -1);
        }
        solve(now, n, 0);
    }

    const int FIRST_SQUARE = 1;

    void run() {
        for (int i = 0; i <= mxW; ++i) {
            for (int j = 0; j <= mxW; ++j) {
                mem[i][j].clear();
            }
        }
        table myEmpty;
        for (int i = 0; i <= mxW; ++i) {
            mem[i][0].push_back(myEmpty);
            if (i != 0) {
                mem[0][i].push_back(myEmpty);
            }
        }
        flag = false;
        assert(mxW >= FIRST_SQUARE);

        for (int w = 1; w <= mxW && !flag; ++w) {
            for (int h = min(w, FIRST_SQUARE); h <= w && !flag; ++h) {
                int sz = mem[w - 1][h - 1].size();
                for (const auto& lastTable : mem[w - 1][h - 1]) {
                    if (flag) break;
                    Solve(lastTable, w - 1, h - 1);
                }
                assert(sz == mem[w - 1][h - 1].size());
            }
        }

        if (!flag) {
            for (int w = mxW; w >= 1; --w) {
                bool ok = false;
                for (int h = w; h >= 1; --h) {
                    if (mem[w][h].empty()) continue;
                    ansTalbe = mem[w][h][0];
                    ok = true;
                    break;
                }
                if (ok) break;
            }
        }

        if (mem[mxW][mxW].size()) {
            cerr << "maximum size faild" << endl;
            assert(false);
        }
    }

    /*void write() {
        //cout << "No" << endl;
        //wrMem();
        cout << "0 0\n";
    }*/

    void solve(int _n, int _mxW, table _tiles, bool & checkFind, table & myAnswer, int& mxN, int& mxM) {
        n = _n;
        mxW = _mxW;
        tiles = _tiles;
        run();
        for (int w = mxW; w >= 1 && mxM == 0; --w) {
            for (int h = w; h >= 1 && mxM == 0; --h) {
                if (!mem[w][h].empty())  {
                    mxN = w, mxM = h;
                    //cout << w << " " << h << endl;
                    //return;
                    
                }
            }
        }
        checkFind = flag;
        myAnswer = ansTalbe;
    }
}

vector<vector<int>> genAllBorders(int c) {
    vector<vector<int>> borders;
    for (int i = 1; i <= c; ++i) {
        for (int j = 1; j <= c; ++j) {
            borders.push_back({i, j});
        }
    }
    /*cout << "borders = " << endl;
    for (auto i : borders) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/ 
    //exit(0);
    return borders;
}

table FUCK = {
    {1, 1, 2, 1},
    {2, 1, 3, 1},
    {3, 1, 4, 1},
    {4, 1, 1, 1}};


vector<vector<int>> genAllTiles(int c) {
    auto borders = genAllBorders(c);
    vector<vector<int>> tiles;
    for (auto i : borders) {
        for (auto j : borders) {
            tiles.push_back({i[0], j[0], i[1], j[1]});       
        }
    }
    sort(all(tiles));
    /*for (auto i : tiles) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    return tiles;
}

const int N = 4;
const int C = 3;
const int W = 12;

int cntCheckHas = 0, cntCheckHasnot = 0;
int cntAns[W][W];
table tiles[W][W];
table sample[W][W];

int cntBad[W][W];
table tiles_bad[W][W];
table sample_bad[W][W];

int mxW = 0, mxH = 0;
int It = 0;
    
void relax(table& setOfTiles) {
    //assert(setOfTiles != FUCK);
    //assert(!(setOfTiles[0] == FUCK[0]));
    ++It;
    if (It % 1000000 == 0) {
        cerr << "check " << It << endl;
    }
    //return;
    bool checkFind = false;
    table myAnswer;
    int w = 0, h = 0;
    Solver::solve(setOfTiles.size(), W, setOfTiles, checkFind, myAnswer, w, h);
    if (checkFind) {
        ++cntCheckHas;
        int n = myAnswer.size();
        int m = myAnswer[0].size();
        ++cntAns[n][m];
        tiles[n][m] = setOfTiles;
        sample[n][m] = myAnswer;
    } else {
        if (tie(w, h) > tie(mxW, mxH)) {
            mxW = w;
            mxH = h;
        }
        ++cntBad[w][h];
        tiles_bad[w][h] = setOfTiles;
        sample_bad[w][h] = myAnswer;
        ++cntCheckHasnot;
    }
}

void rec(int n, int pos, table& now, const vector<vector<int>>& tiles, vector<table>& ans) {
    if (n == now.size()) {  
        //ans.push_back(now);
        //assert(now != FUCK);
        relax(now);
        return;
    }
    if (pos == tiles.size()) {
        return;
    }
    if (now.empty() && (tiles[pos][0] != 1 || tiles[pos][1] != 1)) {
        return;
    }
    rec(n, pos + 1, now, tiles, ans);
    if (now.empty() && (tiles[pos][2] > 2 || tiles[pos][3] > 2)) {
        return;
    }
    now.push_back(tiles[pos]);
    rec(n, pos + 1, now, tiles, ans);
    now.pop_back();
}

vector<table> gen(int n, int c) {
    vector<table> ans;
    auto tiles = genAllTiles(c);
    table now;
    //relax(FUCK);
    rec(n, 0, now, tiles, ans);
    return ans;
}

mt19937 rnd(time(0));

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    /*read();
    run();
    write();*/
    /*int n = 1;
    int mxW = 5;
    table tiles = {{1, 2, 1, 3}};
    bool checkFind = false;
    table myAnswer;
    Solver::solve(n, mxW, tiles, checkFind, myAnswer);
    cout << checkFind << endl;
    if (checkFind) {
        for (auto i : myAnswer) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        } 
    }*/

    
    cout << "number of tiles = " << N << endl;
    cout << "number of colors = " << C << endl;
    cout << "maximum size = " << W << endl;

    //auto forCheck = gen(N, C);
    //shuffle(all(forCheck), rnd);

    //cout << "gen: ok" << endl;
    //cout << "forCheck.size() = " << forCheck.size() << endl;

    //vector<table> forCheck = {{{1, 1, 1, 1}}};

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < W; ++j) {
            cntAns[i][j] = 0;
            tiles[i][j] = {};
            sample[i][j] = {};
            cntBad[i][j] = 0;
            tiles_bad[i][j] = {};
            sample_bad[i][j] = {};
        }
    }

    gen(N, C);

    /*for (auto setOfTiles : forCheck) {
        ++It;
        if (It % 100000 == 0) {
            cerr << "check " << It << endl;
        }
        bool checkFind = false;
        table myAnswer;
        int w = 0, h = 0;
        Solver::solve(setOfTiles.size(), W, setOfTiles, checkFind, myAnswer, w, h);
        if (checkFind) {
            ++cntCheckHas;
            int n = myAnswer.size();
            int m = myAnswer[0].size();
            ++cntAns[n][m];
            tiles[n][m] = setOfTiles;
            sample[n][m] = myAnswer;
        } else {
            if (tie(w, h) > tie(mxW, mxH)) {
                mxW = w;
                mxH = h;
            }
            ++cntBad[w][h];
            tiles_bad[w][h] = setOfTiles;
            sample_bad[w][h] = myAnswer;
            ++cntCheckHasnot;
        }
    }*/

    cout << "number of checked sets = " << It << endl;
    cout << "number of periodic sets = " << cntCheckHas << endl;
    cout << "number of non tiling sets = " << cntCheckHasnot << endl;
    cout << "maximum non tiling rectangle = " << mxW << " " << mxH << endl;

    for (int n = 1; n < W; ++n) {
        for (int m = 1; m < W; ++m) {
            if (cntAns[n][m] == 0) continue;
            cout << "n = " << n << " m = " << m << " cnt = " << cntAns[n][m] << endl;
        }
    }

    while (true) {
        cout << "input type of query (0 - get periodic set, 1 - get non periodic set)" << endl;
        int type;
        cin >> type;
        cout << "input n, m (number of column ans number of rows)" << endl;
        int n, m;
        cin >> n >> m;
        if (type == 0) { 
            if (cntAns[n][m]) {
                cout << "Yes, we have this minumum period" << endl;
                cout << "Set of tiles:" << endl;
                for (auto i : tiles[n][m]) {
                    for (auto x : i) {
                        cout << x << " ";
                    }
                    cout << endl;
                }
                cout << "minumum period:" << endl;
                for (auto x : sample[n][m]) {
                    for (auto y : x) {
                        cout << y << " ";
                    }
                    cout << endl;
                }
            } else {
                cout << "No, we haven't this minumum period" << endl;
            }
            cout << endl;
        } else if (type == 1) {
            if (cntBad[n][m]) {
                cout << "Yes, we have this non tiling set" << endl;
                cout << "Set of tiles:" << endl;
                for (auto i : tiles_bad[n][m]) {
                    for (auto x : i) {
                        cout << x << " ";
                    }
                    cout << endl;
                }
                cout << "tiled rectangle" << endl;
                for (auto x : sample_bad[n][m]) {
                    for (auto y : x) {
                        cout << y << " ";
                    }
                    cout << endl;
                }
            } else {
                cout << "No, we haven't this non tiling set" << endl;
            }
            cout << endl;
        } else {
            assert(false);
        }
    }

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