#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < n; ++i)

using namespace std;

typedef long long ll;
typedef long double ld;

//#ifdef LOCAL
#define io freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
//#else
//#define io ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)
//#endif

struct event {
    int x, y, time;
    vector<int> g;
};

vector<vector<int>> g;
vector<int> v_pair;
vector<int> used;
int used_ctr = 0;

bool dfs(int v, int p) {
    used[v] = used_ctr;
    if (p == -1) {
        for (int u : g[v]) {
            if (u == v_pair[v]) continue;
            if (used[u] != used_ctr && dfs(u, v)) {
                v_pair[v] = u;
                return true;
            }
        }
        return false;
    } else {
        if (v_pair[v] == -1 || (used[v_pair[v]] != used_ctr && dfs(v_pair[v], -1))) {
            v_pair[v] = p;
            return true;
        } else return false;
    }
}

void dfs_count(int v) {
    used[v] = used_ctr;
    for (int u : g[v]) 
        if (used[u] != used_ctr) 
            dfs_count(u);
}

int main() {
    io;

    int n;
    cin >> n;

    vector<event> events;
    events.reserve(n);

    forn(i, n) {
        string s;
        int x1, y1, x2, y2;
        cin >> s >> x1 >> y1 >> x2 >> y2;
        int mm = stoi(s.substr(0, 2)) * 60 + stoi(s.substr(3, 2));

        for (auto &event : events) {
            if (event.time + abs(event.x - x1) + abs(event.y - y1) >= mm) break;
            event.g.push_back(events.size());
        }

        mm += abs(x2 - x1) + abs(y2 - y1);
        events.push_back({x2, y2, mm});
    }


    g.resize(2 * n);
    v_pair.assign(2 * n, -1);
    used.assign(2 * n, -1);

    forn(v, n) {
        auto &event = events[v];
        for (int u : event.g) {
            g[v].push_back(u + n);
        }
    }

    for (int i = 0; i < n; i++) {
        if (v_pair[i] == -1) {
            dfs(i, -1);
            used_ctr++;
        }
    }

    g.assign(n, vector<int>());
    forn(i, n) if (v_pair[i] != -1) {
            g[i].push_back(v_pair[i] - n);
            g[v_pair[i] - n].push_back(i);
        }

    int ctr = 0;
    forn(i, n) if (used[i] != used_ctr) {
            dfs_count(i);
            ctr++;
        }
    //cerr << ctr;
    cout << ctr;
}