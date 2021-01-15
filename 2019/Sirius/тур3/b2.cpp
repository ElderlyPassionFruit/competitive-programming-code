#include <bits/stdc++.h>
 
using namespace std;
//#define int long long
const int MAXN = 1e5 + 10;
vector <int> g[MAXN];
int n, m;
void read() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
}
 
unordered_set <int> used[MAXN];
int fans[MAXN];
int pos = 0;
void dfs(int v) {
    for (auto i : g[v]) {
        int a = v;
        int b = i;
        if (used[a].find(b) == used[a].end()) {
            used[b].insert(a);
            used[a].insert(b);
            dfs(i);
        }
    }
    fans[pos++] = v;
}
 
deque <int> ans;
void run() {
    dfs(0);
    /*cout << "fans = " << endl;
    for (auto i : fans) {
        cout << i + 1 << " ";
    }*/
    //cout << endl;
    unordered_set <int> used;
    int cnt = 0;
    for (int i = 0; i < pos; i++) {
        int new_v = fans[i];
        if (used.find(new_v) == used.end()) {
            used.insert(new_v);
            ans.push_back(new_v);
            cnt++;
        }
        else {
            while (ans[cnt - 1] != new_v) {
                cout << ans[cnt - 1] + 1 << " ";
                auto it = used.find(ans[cnt - 1]);
                used.erase(it);
                cnt--;
                ans.pop_back();
            }
            cout << new_v + 1 << '\n';
        }
    }
}
 
void write() {
//  cout << "ans = " << endl;
/*  for (int i = 1; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] + 1 << " ";
        }
        cout << endl;
    }*/
}
 
signed main() {
    freopen("postmen.in", "r", stdin);
    freopen("postmen.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}