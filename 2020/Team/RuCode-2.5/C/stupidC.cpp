#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int getMod(int a) {
    while (a < 0) a += MOD;
    while (a >= MOD) a -= MOD;
    return a;
}

int add(int a, int b) {
    a = getMod(a);
    b = getMod(b);
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a = getMod(a);
    b = getMod(b);
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    a = getMod(a);
    b = getMod(b);
    return (ll) a * b % MOD;
}

int binpow(int a, int n) {
    a = getMod(a);
    int ans = 1;
    while (n) {
        if (n & 1) {
            ans = mul(ans, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

int getInv(int a) {
    return binpow(a, MOD - 2);
}

struct Pt{
    int x, y;
};

int n, myDet;
vector<vector<int>> a;
vector<Pt> have;
int m;

int getDet(vector<vector<int>> a) {
    int n = a.size();
    int fDiv = 1;
    for (int i = 0; i < n; ++i) {
        if (!a[i][i]) {
            for (int j = i + 1; j < n; ++j) {
                if (a[j][i]) {
                    swap(a[i], a[j]);
                    fDiv = mul(fDiv, getMod(-1));
                    break;
                }
            }
            if (!a[i][i]) return 0;
        }
        for (int j = i + 1; j < n; ++j) {
            if (!a[j][i]) continue;
            int x = a[i][i];
            int y = a[j][i];
            fDiv = mul(fDiv, x);
            fDiv = mul(fDiv, y);
            for (int k = i; k < n; ++k) {
                a[i][k] = mul(a[i][k], y);
                a[j][k] = mul(a[j][k], x);
                a[j][k] = sub(a[j][k], a[i][k]);
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        ans = mul(ans, a[i][i]);
    }
    ans = mul(ans, getInv(fDiv));
    return ans;
}

vector<vector<int>> ans;

void relax(vector<int> now) {
    /*cout << "now = ";
    for (auto i : now) {
        cout << i << " ";
    }
    cout << endl;*/
    /*int fansDet = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        int myMul = poly[mask];
        for (int bit = 0; bit < m; ++bit) {
            if (!((mask >> bit) & 1)) continue;
            myMul = mul(myMul, now[bit]);
        }
        fansDet = add(fansDet, myMul);
    } */  
    /*if (now[0] == 1 && now[1] == 2) {
        cout << "fansDet = " << fansDet << endl;
    }*/
    for (int i = 0; i < m; ++i) {
        a[have[i].x][have[i].y] = now[i];
    }
    int fansDet = getDet(a);
    if (fansDet == myDet) {
        ans.push_back(now);
    }
    cout << "now = ";
    for (auto i : now) cout << i << " ";
    cout << "fansDet = " << fansDet << endl;
}

void gen(vector<int> now) {
    //if (ans.size() > 1) return;
    if (now.size() == m) {
        relax(now);
        return;
    } 
    now.push_back(0);
    for (int i = 0; i < 10; ++i) {
        now[now.size() - 1] = i;
        gen(now);
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> n >> myDet;
    a.resize(n, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char x;
            cin >> x;
            if (x == '*') {
                have.push_back({i, j});
            } else {
                a[i][j] = x - '0';
            }
        }
    }
    m = have.size();
    //relax({1, 3});
    //exit(0);
    gen({});
    return 0;
    if (ans.size() == 0) {
        cout << "error\n";
    } else if (ans.size() > 1) {
        cout << "ambiguous\n";
    } else {
        cout << "unique\n";
        for (int i = 0; i < m; ++i) {
            a[have[i].x][have[i].y] = ans[0][i];
        }
        for (auto i : a) {
            for (auto j : i) {
                cout << j;
            }   
            cout << "\n";
        }
    }
    return 0;
}