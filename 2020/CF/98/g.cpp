#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Edge{
    int to, bestCost;
};

const int N = 2e5 + 10;
//const int N = 100;
int n, k;
vector<Edge> g[N];

vector<int> ban;

void read() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({v, 0});
        g[v].push_back({u, 0});
    }
    cin >> k;
    ban.resize(k);
    for (auto& v : ban) {
        cin >> v;
        --v;
    }
}

int cost[N];

void initCost() {
    fill(cost, cost + n, -1);
    queue<int> q;
    for (auto v : ban) {
        q.push(v);
        cost[v] = 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [to, bestCost] : g[v]) {
            if (cost[to] != -1) continue;
            cost[to] = cost[v] + 1;
            q.push(to);
        }
    }
    for (int v = 0; v < n; ++v) {
        multiset<int> best;
        //best.insert(cost[i]);
        for (auto [to, bestCost] : g[v]) {
            best.insert(cost[to] + 1);
        }
        //best.insert(cost[v] - 1);
        for (auto& i : g[v]) {
            best.erase(best.find(cost[i.to] + 1));
            i.bestCost = *best.begin();
            best.insert(cost[i.to] + 1);
        }
    }
}

int fenwick[N];
//int mySize;
int uptates[N];
int topU = 0;

void clear() {
    //have.clear();
    //mySize = size;
    /*for (int i = 0; i <= size; ++i) {
        fenwick[i] = 0;
    }*/
    for (int i = 0; i < topU; ++i) {
        for (int pos = uptates[i]; pos < N; pos |= pos + 1) {
            fenwick[pos] = 0;
        }
    }
    topU = 0;
}

int ans[N];

bool used[N];
int sz[N];
int centr;

void dfsCentr(int v, int p, int size) {
    sz[v] = 1;
    int mx = 0;
    for (auto [to, bestCost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfsCentr(to, v, size);
        chkmax(mx, sz[to]);
        sz[v] += sz[to]; 
    }
    chkmax(mx, size - sz[v]);
    if (mx <= size / 2) {
        centr = v;
    }
}

void add(int maxD, int cost) {
    int pos = n - maxD;
    assert(pos >= 0);
    uptates[topU++] = pos;
    //cout << "maxD = " << maxD << " cost = " << cost << endl;
    for (int i = pos; i < N; i |= i + 1) {
        chkmax(fenwick[i], cost);
    }
}

void dfsAdd(int v, int p, int maxD, int dist) {
    //chkmin(maxD, cost[v] - dist);
    if (maxD < 0) return;
    if (cost[v] == 0) return;
    chkmin(maxD, cost[v] - dist - 1);
    add(maxD, cost[v]);
    //if (maxD < 0) return;

    for (auto [to, bestCost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfsAdd(to, v, min(maxD, bestCost - dist -  1), dist + 1);
    }
}

int getAns(int dist) {
    int pos = n - dist;
    int ans = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        chkmax(ans, fenwick[i]);
    }
    return ans;
    /*for (auto i : have) {
        if (i.first < dist) continue;
        chkmax(ans, i.second);
    }*/
    //return ans;
}

void dfsSolve(int v, int p, int maxD, int dist) {
    //chkmin(maxD, cost[v] - dist);
    if (maxD < 0) return;
    if (cost[v] == 0) return;
    chkmax(ans[v], getAns(dist));
    chkmin(maxD, cost[v] - dist - 1);
    //if (maxD < 0) return;

    for (auto [to, bestCost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfsSolve(to, v, min(maxD, bestCost - dist - 1), dist + 1);
    }
}

void solve(int v, int size) {
    centr = -1;
    dfsCentr(v, -1, size);
    assert(centr != -1);
    v = centr;
    used[v] = true;
    //cout << "SOLVE = " << v << endl;

    //cout << "v = " << v << endl;

    clear();
    add(cost[v], cost[v]);
    for (auto [to, bestCost] : g[v]) {
        if (used[to]) continue;
        //cout << "i = " << i << endl;    
        dfsSolve(to, v, bestCost - 1, 1);
        dfsAdd(to, v, bestCost - 1, 1);
    }

    //cout << "firstPart = " << endl;

    /*cout << "have = " << endl;
    for (auto i : have) {
        cout << i.first << " " << i.second << endl;
    }*/

    if (cost[v] > 0) { 
        chkmax(ans[v], getAns(0));
    }

    reverse(all(g[v]));
    // copy-paste
    

    //cout << "secondPart = " << endl;
    clear();

    for (auto [to, bestCost] : g[v]) {
        if (used[to]) continue;
        //cout << "i = " << i << endl;    
        dfsSolve(to, v, bestCost - 1, 1);
        dfsAdd(to, v, bestCost - 1, 1);
    }

    //return;

    for (auto [to, bestCost] : g[v]) {
        if (used[to]) continue;
        /*cout << "v = " << v << " i = " << i << endl;
        cout << "used = " << endl;
        for (int x = 0; x < n; ++x) {
            cout << used[x] << ' ';
        }
        cout << endl;*/
        int fsz = sz[to];
        if (fsz > sz[v]) {
            fsz = size - sz[v];
        }
        solve(to, fsz);
    }
}

void run() {
    initCost();
    //cout << "initCost : Ok" << endl;
    for (int i = 0; i < n; ++i) {
        ans[i] = cost[i];
    }
    solve(0, n);
}

void write() {
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}