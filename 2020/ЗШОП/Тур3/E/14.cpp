#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

int n, q;
vector<int> a;

void read() {
  cin >> n >> q;
  a.resize(n);
  for (auto &i : a)
    cin >> i;
}

struct segment_tree{
  vector<int> tree;
  int n;
  segment_tree() {}

  void build(int v, int tl, int tr, const vector<int> & a) {
    if (tl == tr - 1) {
      tree[v] = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm, tr, a);
    tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
  }

  segment_tree(const vector<int> & a) {
    n = a.size();
    tree.resize(4 * n, 0);
    build(1, 0, n, a);
  }

  int get(int v, int tl, int tr, int l, int r) {
    if (tl >= r || tr <= l) return 0;
    if (tl >= l && tr <= r) return tree[v];
    int tm = (tl + tr) / 2;
    return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
  }

  int get(int l, int r) {
    chkmax(l, 0);
    return get(1, 0, n, l, r + 1);
  }
};

struct event{
  int t, l, r;
  event() {}
};

vector<event> have;

void run() {
  segment_tree tree(a);
  have.resize(q);
  set<int> x;
  for (auto &i : have) {
    cin >> i.t >> i.l >> i.r;
    i.l--;
    i.r--;
    x.insert(i.t);
  }
  if (x.size() == 1) {
    for (int i = 0; i < n; i++) {
      a[i] = tree.get(i - *x.begin(), i);
    } 
    for (int i = 1; i < n; i++)
      a[i] += a[i - 1];
  }
  for (auto [t, l, r] : have) {
    if (x.size() == 1) {
      cout << a[r] - (l > 0 ? a[l - 1] : 0) << "\n";
      continue;
    }
    ll ans = 0;
    for (int i = l; i <= r; i++)
      ans += tree.get(i - t, i);
    cout << ans << "\n";
  }
}

void write() {

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