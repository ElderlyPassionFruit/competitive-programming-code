#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<pair<int, int>> have;
vector<vector<int>> g;

bool check(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) * abs(a.second - b.second) == 2;
}

void gen() {
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            int g = __gcd(x, y);
            if (g != 1) continue;
            have.push_back({x, y});
        }
    }
    g.resize(have.size());
    for (int i = 0; i < have.size(); ++i) {
        for (int j = 0; j < have.size(); ++j) {
            if (check(have[i], have[j])) {
                g[i].push_back(j);
            }
        }
    }
}

vector<pair<int, int>> ans;

vector<bool> used;
vector<int> p;
void bfs(int from, int to) {
    queue<int> q;
    q.push(from);
    p.assign(have.size(), -1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto i : g[v]) {
            if (p[i] != -1) continue;
            p[i] = v;
            if (to == i) {
                while (!q.empty()) {
                    q.pop();
                }
                break;
            }
            q.push(i);
        }
    }
    /*cout << "from = " << from << " to = " << to << endl;
    cout << "p = " << endl;
    for (auto i : p) {
        cout << i << " ";
    } 
    cout << endl;*/
    if (p[to] == -1) {
        cout << "-1\n";
        exit(0);
    }
    vector<pair<int, int>> fans;
    while (to != from) {
        used[to] = true;
        fans.push_back(have[to]);
        to = p[to];
    }
    reverse(all(fans));
    for (auto i : fans) {
        ans.push_back(i);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    gen();
    /*cout << have.size() << endl;
	for (auto i : have) {
        cout << i.first << "/" << i.second << endl;
    }*/
    used.resize(have.size());
    int now = 0;
    ans.push_back(have[0]);
    used[0] = true;
    for (int i = 0; i < have.size(); ++i) {
        if (used[i]) continue;
        bfs(now, i);
        now = i;
    }
    assert(ans.size() <= 20000);
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i.first << " / " << i.second << " ";
    }
    cout << "\n";
    return 0;
}