#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18;
 
 
template<int SZ>
struct MaxFlow {
  struct Edge {
    int to, rev;
    ll cap, flow;
 
    Edge(int to, int rev, ll cap, ll flow) : to(to), rev(rev), cap(cap), flow(flow) {};
  };
  
  vector<Edge> g[SZ];
 
  void addEdge(int u, int v, ll cap) {
    Edge a(v, (int) g[v].size(), cap, 0LL);
    Edge b(u, (int) g[u].size(), 0LL, 0LL);
    g[u].push_back(a);
    g[v].push_back(b);
  }
 
  int ST, EN, level[SZ], ind[SZ];
 
  bool bfs() {
    for (int i = 0; i < SZ; i++) {
      level[i] = -1;
      ind[i] = 0;
    }
    level[ST] = 0;
    queue<int> q;
    q.push(ST);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (Edge e : g[u]) {
        if (level[e.to] == -1 && e.flow < e.cap) {
          q.push(e.to);
          level[e.to] = level[u] + 1;
        }
      }
    }
    return level[EN] >= 0;
  }
  
  ll dfs(int v, ll flow) {
    if (v == EN) {
      return flow;
    }
    for (; ind[v] < g[v].size(); ind[v]++) {
      Edge &e = g[v][ind[v]];
      if (level[e.to] != level[v] + 1 || e.cap == e.flow) {
        continue;
      }
      ll new_f = dfs(e.to, min(flow, e.cap - e.flow));
      if (new_f) {
        e.flow += new_f;
        g[e.to][e.rev].flow -= new_f;
        return new_f;
      }
    }
    return 0;
  }
 
  ll maxFlow(int st, int en) {
    ST = st;
    EN = en;
    ll ans = 0;
    while (bfs()) {
      ll flow = dfs(ST, LLONG_MAX);
      while (flow) {
        ans += flow;
        flow = dfs(ST, LLONG_MAX);
      }
    }
    return ans;
  }
};

vector<vector<int>> g;

int main() {
  int n, k;
  cin >> n >> k;
  MaxFlow<302> mf;
  vector<int> a;
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    a.push_back(x - 1);
    mf.addEdge(0, x + 1, 1);
  }
  set <int> b;
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    b.insert(x - 1);
    mf.addEdge(x + 1, 1, 1);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      if (c == '1') {
        mf.addEdge(i + 2, j + 2, INF);
      }
    }
  }
  if (mf.maxFlow(0, 1) < k) {
    cout << "NO" << endl;
    return 0;
  }
  vector<pair<int, int>> edges;
  for (int i = 0; i < 302; i++) {
    for (auto e : mf.g[i]) {
      if (e.cap != 0) {
        for (int j = 0; j < e.flow; j++) {
          edges.push_back({i, e.to});
        }
      }
    }
  }
  /*for (auto el : edges) {
    cout << el.first << " " << el.second << endl;
  }*/

  multiset<pair <int, int> > fans;
  for (auto el : edges) {
    if (el.first < 2 || el.second < 2)
      continue;
    fans.insert({el.first - 2, el.second - 2});
  }

  set<int> have;
  for (auto i : a)
    have.insert(i);
  cout << "YES" << "\n";
  vector<pair <int, int> > ans;
  while (!fans.empty()) {
    bool flag = false;
    for (auto i : fans) {
      if (have.count(i.first) && !have.count(i.second)) {
        flag = true;
        ans.push_back(i);
        have.erase(have.find(i.first));
        have.insert(i.second);
        fans.erase(fans.find(i));
        break;
      }
    }
    if (have == b)
      break;
    assert(flag);
  }
  cout << ans.size() << "\n";
  for (auto i : ans)
    cout << i.first + 1 << " " << i.second + 1 << "\n";
}