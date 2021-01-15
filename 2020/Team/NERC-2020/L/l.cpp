#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 2e5 + 10;
int n, q;
int val[N];
int minVal[N], maxVal[N];
vector<int> g[N];
vector<pair<int, int>> segs;

void dfs(int v) {
    minVal[v] = maxVal[v] = val[v];
    for (auto i : g[v]) {
        dfs(i);
        minVal[v] = min(minVal[v], minVal[i]);
        maxVal[v] = max(maxVal[v], maxVal[i]);
    }
}

bool checkCross(int a, int b, int c, int d) {
    return max(a, c) <= min(b, d);
}

int ans[N];

const int MEM = 2 * N + 2 * N + 228;
int fenwick[MEM];

void upd(int pos, int val) {
    for (; pos < MEM; pos |= pos + 1) {
        fenwick[pos] += val;
    }
}

int get(int r) {
    int ans = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        ans += fenwick[r];
    }
    return ans;
}

int get(int l, int r) {
    return get(r) - get(l - 1);
}

vector<int> L[MEM];
vector<int> R[MEM];
vector<pair<int, int>> qL[MEM];

void process() {
    /*for (int i = 0; i < q; ++i) {
        ans[i] = 0;
        for (int j = 0; j < n; ++j) {
            ans[i] += checkCross(segs[i].first, segs[i].second, minVal[j], maxVal[j]);
            ans[i] -= segs[i].first <= minVal[j] && maxVal[j] <= segs[i].second;
        }
    }*/
    for (int i = 0; i < n; ++i) {
        L[maxVal[i]].push_back(minVal[i]);
        R[minVal[i]].push_back(maxVal[i]);
    }
    for (int i = 0; i < q; ++i) {
        qL[segs[i].second].push_back({segs[i].first, i});
    }
    fill(ans, ans + q, 0);
    fill(fenwick, fenwick + MEM, 0);
    for (int i = 0; i < MEM; ++i) {
        for (auto pos : L[i]) {
            upd(pos, 1);
        }
        for (auto [l, ind] : qL[i]) {
            ans[ind] -= get(l, i);
        }
    }
    fill(fenwick, fenwick + MEM, 0);
    for (int i = 0; i < MEM; ++i) {
        for (auto pos : R[i]) {
            upd(pos, 1);
        }
        for (auto [l, ind] : qL[i]) {
            ans[ind] += get(l, MEM - 1);
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        cin >> val[i];
        if (l != -1) {
            g[i].push_back(l);
        }
        if (r != -1) {
            g[i].push_back(r);
        }
    }
    dfs(0);
    //int q;
    //vector<pair<int, int>> segs(q);
    cin >> q;
    segs.resize(q);
    vector<int> coord;
    for (auto& [l, r] : segs) {
        cin >> l >> r;
        coord.push_back(l);
        coord.push_back(r);
    }
    for (int i = 0; i < n; ++i) {
        coord.push_back(minVal[i]);
        coord.push_back(maxVal[i]);
    }
    sort(all(coord));
    coord.resize(unique(all(coord)) - coord.begin());
    for (auto& [l, r] : segs) {
        l = lower_bound(all(coord), l) - coord.begin();
        r = lower_bound(all(coord), r) - coord.begin();
    }
    for (int i = 0; i < n; ++i) {
        minVal[i] = lower_bound(all(coord), minVal[i]) - coord.begin();
        maxVal[i] = lower_bound(all(coord), maxVal[i]) - coord.begin();   
    }
    process();
    for (int i = 0; i < q; ++i) {
        cout << ans[i] * 2 + 1 << '\n';
    }
    return 0;
}









