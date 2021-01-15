#include <bits/stdc++.h>
 
using namespace std;
#define int long long
 
vector <pair <int, pair <int, int> > > help;
vector <vector <int> > table;
 
int n, m;
void read() {
    cin >> n >> m;
    table.assign(n, vector <int> (m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
            help.push_back({table[i][j], {i, j}});
        }
    }
} 
 
const int MAXN = 2 * 1e6;
 
int maxH[MAXN], maxW[MAXN];
int par[MAXN];
map <int, int> mx_num;
 
void make_set(int v) {
    par[v] = v;
}
 
int find_pred(int v) {
    if (par[v] == v) return v;
    return par[v] = find_pred(par[v]);
}
 
void union_set(int v, int u) {
    v = find_pred(v);
    u = find_pred(u);
    if (v == u)
        return;
    par[u] = v;
    mx_num[v] = max(mx_num[v], mx_num[u]);
}
 
 
void run() {
    sort(help.begin(), help.end());
    for (int i = 0; i < help.size(); i++) {
        int j;
        for (j = i; j < help.size(); j++) {
            if (help[j].first != help[i].first) 
                break;
        }
        j--;
        if (j >= help.size()) {
            while (true) {
                int a = 0;
            }
        } 
        map<int, vector <pair <int, int> > > pos_x, pos_y;
        map <pair <int, int>, int> for_v;
        pos_x.clear();
        pos_y.clear();
        mx_num.clear();
        for_v.clear();
 
        for (int k = i; k <= j; k++) {
            pair <int, int> point = help[k].second;
            int x = point.first;
            int y = point.second;
            int v = k - i + 1;
 
            for_v[point] = v;
            make_set(v);
            pos_x[x].push_back(point);
            pos_y[y].push_back(point);
 
            mx_num[v] = max(maxW[x], maxH[y]);
        }
 
        for (auto t : pos_x) {
            for (auto k : t.second) {
                int v = for_v[t.second[0]];
                int u = for_v[k];
                union_set(v, u);
            }
        }
 
        for (auto t : pos_y) {
            for (auto k : t.second) {
                int v = for_v[t.second[0]];
                int u = for_v[k];
                union_set(v, u);
            }
        }
 
        for (int k = i; k <= j; k++) {
            pair <int, int> point = help[k].second;
            int x = point.first;
            int y = point.second;
            int v = for_v[point];
            v = find_pred(v);
            int best = mx_num[v];
 
            table[x][y] = best + 1;
            maxH[y] = best + 1;
            maxW[x] = best + 1;
        }
 
        i = j;
    }
}
 
void write() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << table[i][j] << " ";
        }
        cout << '\n';
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}