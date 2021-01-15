#include <bits/stdc++.h>

using namespace std;
using ll = unsigned long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Edge{
    int to, len;
    Edge() {}
    Edge(int _to, int _len) {
        to = _to, len = _len;
    }
};

const int N = 2e5 + 10;
int n;
vector<Edge> g[N];
ll cntPath;
ll wPath;
bool color[N][3];

ll dp[N][1 << 3];
ll cntMask[N][1 << 3];

int ppc[1 << 3];

void relax0(int v) {
    for (int mask = 1; mask < (1 << 3); ++mask) {
        bool ok = true;
        for (int bit = 0; bit < 3; ++bit) {
            if (!((mask >> bit) & 1)) continue;
            ok &= color[v][bit];
        }
        if (ok) {
            cntMask[v][mask] = 1;
        }
    } 
}

ll get(int to, int len, int mask) {
    ll ans = dp[to][mask];
    if (ppc[mask] == 1 || ppc[mask] == 2) {
        ans += cntMask[to][mask] * len;
    }
    return ans;
    //return dp[to][mask] + cntMask[to][mask] * (ppc[mask] == 1 || ppc[mask] == 2) * len;
}

ll sumDp[1 << 3];
ll sumCnt[1 << 3];
ll resultDp[1 << 3];
ll resultCnt[1 << 3];

void initResult(int to, int len, int mask1) {
    for (int mask2 = 0; mask2 < (1 << 3); ++mask2) {
        if (mask1 & mask2) continue;
        int nxtMask = mask1 | mask2;
        resultDp[nxtMask] += get(to, len, mask1) * sumCnt[mask2] + sumDp[mask2] * cntMask[to][mask1];
        resultCnt[nxtMask] += cntMask[to][mask1] * sumCnt[mask2];
    }
}

void relax2(int v, int p) {
    fill(sumDp, sumDp + (1 << 3), 0);
    fill(sumCnt, sumCnt + (1 << 3), 0);
    fill(resultDp, resultDp + (1 << 3), 0);
    fill(resultCnt, resultCnt + (1 << 3), 0);
    sumCnt[0] = 1;
    resultCnt[0] = 1;
    //cout << "puhh" << endl;
    for (auto [to, len] : g[v]) {
        if (to == p) continue;
        for (int mask1 = 1; mask1 < (1 << 3); ++mask1) {
            for (int maskC = 0; maskC < (1 << 3); ++maskC) {
                if (maskC & mask1) continue;
                bool ok = true;
                for (int bit = 0; bit < 3; ++bit) {
                    if (!((maskC >> bit) & 1)) continue;
                    ok &= color[v][bit];
                }
                if (!ok) continue;
            
                for (int mask2 = 0; mask2 < (1 << 3); ++mask2) {
                    if (maskC & mask2) continue;
                    if (mask1 & mask2) continue;
                    int nxtMask = mask1 | mask2 | maskC;
                    ll dpL = get(to, len, mask1);
                    ll cntL = cntMask[to][mask1];

                    ll dpR = resultDp[mask2];
                    ll cntR = resultCnt[mask2];

                    dp[v][nxtMask] += dpL * cntR + dpR * cntL;
                    cntMask[v][nxtMask] += cntL * cntR; 
                }
            }
        }

        for (int mask = 1; mask < (1 << 3); ++mask) {
            initResult(to, len, mask);
        }
        
        for (int mask = 1; mask < (1 << 3); ++mask) {
            sumDp[mask] += get(to, len, mask);
            sumCnt[mask] += cntMask[to][mask];
        }
    }
}

void dfs(int v, int p) {
    for (auto [to, len] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    relax0(v);
    //relax1(v, p);
    relax2(v, p);
}

string getMask(int mask) {
    string ans;
    for (int bit = 0; bit < 3; ++bit) {
        ans += ((mask >> bit) & 1) + '0';
    }
    return ans;
}
mt19937 rnd(time(0));

void solve() {
    ppc[0] = 0;
    for (int mask = 1; mask < (1 << 3); ++mask) {
        ppc[mask] = ppc[mask >> 1] + (mask & 1);
    }
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < (1 << 3); ++mask) {
            dp[i][mask] = cntMask[i][mask] = 0;
        }
    }
    /*cout << "ppc = " << endl;
    for (int i = 0; i < (1 << 3); ++i) {
        cout << ppc[i] << " ";
    }
    cout << endl;*/
    int root = (rnd() % n + n) % n;
    dfs(root, -1);
    /*cout << "dp = " << endl;
    for (int v = 0; v < n; ++v) {
        cout << "v = " << v << endl;
        cout << "dp, cnt = " << endl;
        for (int mask = 0; mask < (1 << 3); ++mask) {
            cout << getMask(mask) << " " << dp[v][mask] << " " << cntMask[v][mask] << endl;
        }
    }
    cout << endl;*/
    wPath = dp[root][(1 << 3) - 1];
    assert(cntPath == cntMask[root][(1 << 3) - 1]);
}

void outAns() {
    cout << (ld) wPath / cntPath << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cout.setf(ios::fixed);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, len;
        cin >> u >> v >> len;
        --u;
        --v;
        g[u].push_back({v, len});
        g[v].push_back({u, len});
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            color[i][j] = false;
        }
    }
    cntPath = 1;
    for (int c = 0; c < 3; ++c) {
        int m;
        cin >> m;
        cntPath = cntPath * m;
        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            --x;
            color[x][c] = true;
        }
    }
    solve();
    outAns();
	return 0;
}