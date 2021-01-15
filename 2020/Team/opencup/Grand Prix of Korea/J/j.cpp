#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Pt{
    int x, y;
    Pt() {}
    Pt(int _x, int _y) {
        x = _x, y = _y;
    }
};

Pt operator-(const Pt& a, const Pt& b) {
    return Pt(a.x - b.x, a.y - b.y);
}

Pt operator+(const Pt& a, const Pt& b) {
    return Pt(a.x + b.x, a.y + b.y);
}

bool operator<(const Pt& a, const Pt& b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}

const int N = 3e5 + 10;
//const int N = 100;
int n;
string s;

const vector<int> dx = {1, -1, 0, 0};
const vector<int> dy = {0, 0, 1, -1};

int getDir(char x) {
    if (x == 'R') return 0;
    if (x == 'L') return 1;
    if (x == 'U') return 2; 
    if (x == 'D') return 3;
    assert(false);
    return -1;
}

const vector<Pt> base = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

Pt dp[N][4];

map<Pt, int> vec;
int myDx = 0, myDy = 0;

void build() {
    for (int it = 0; it < 4; ++it) {
        dp[n][it] = base[it];
    }

    map<Pt, int> fans;
    int ndx = 0, ndy = 0;
    
    for (int i = n - 1; i >= 0; --i) {
        int ndir = getDir(s[i]);
        //cout << "i = " << i << " ndir = " << ndir << endl;
        ndx += dx[ndir];
        ndy += dy[ndir];
        for (int it = 0; it < 4; ++it) {
            Pt now = base[it];
            now.x += dx[ndir];
            now.y += dy[ndir];
            if (now.x == 0 && now.y == 0) {
                dp[i][it] = dp[i + 1][it];
            } else {
                int lastI = n;
                Pt lastPt = base[it];
                lastPt.x += ndx;
                lastPt.y += ndy;

                for (int lastIt = 0; lastIt < 4; ++lastIt) {
                    Pt have = base[it] - base[lastIt];
                    have.x += ndx;
                    have.y += ndy;
                    auto myIt = fans.find(have);
                    if (myIt == fans.end()) continue;
                    if (myIt->second >= lastI) continue;
                    lastI = myIt->second;
                    lastPt = dp[lastI][lastIt];
                }

                dp[i][it] = lastPt;
            }
        }
        fans[{ndx, ndy}] = i;
    }
    /*cout << "base = " << endl;
    for (auto i : base) {
        cout << i.x << " " << i.y << endl;
    }
    cout << "dp = " << endl;
    for (int i = 0; i <= n; ++i) {
        for (int it = 0; it < 4; ++it) {
            cout << dp[i][it].x << " " << dp[i][it].y << " | ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; ++i) {
        if (!vec.count({myDx, myDy})) {
            vec[{myDx, myDy}] = i;
        }
        int myDir = getDir(s[i]);
        myDx += dx[myDir];
        myDy += dy[myDir];
    }
    /*cout << "vec = " << endl;
    for (auto i : vec) {
        cout << i.first.x << " " << i.first.y << " | " << i.second << endl;
    }*/
}

void solve() {
    Pt s;
    cin >> s.x >> s.y;
    int t = n;
    Pt ans = s;
    ans.x += myDx;
    ans.y += myDy;
    for (int it = 0; it < 4; ++it) {
        Pt have = base[it] - s;
        auto myIt = vec.find(have);
        if (myIt == vec.end()) continue;
        if (myIt->second >= t) continue;
        //cout << "it = " << it << endl;
        t = myIt->second;
        ans = dp[t][it];
    }
    cout << ans.x << " " << ans.y << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> s;
    build();
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
	return 0;
}