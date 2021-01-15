#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
const int MAXN = 3e5 + 10;

struct edge{
	int v, ind;
	edge() {}
	edge(int a, int b) {
		v = a;
		ind = b;
	}
};

pair<int, vector<edge>> g[MAXN], g2[MAXN];

bool cmp(pair<int, vector<edge> > & a, pair<int, vector<edge> > & b) {
	return a.second.size() < b.second.size();
}

int ed[MAXN];

inline void add(int a) {
	ed[a]++;
}

void print_ans() {
	ll ans = 0;
	for (int i = 0; i < MAXN; i++) {
		ans += (ll) ed[i] * (ed[i] - 1) / 2;
	}
	cout << ans << endl;
}

int ind[MAXN], mark[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//cout.precision(20);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		g[i] = {i, {}};
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].second.push_back({b, i + 1});
		g[b].second.push_back({a, i + 1});
	}

	sort(g, g + n, cmp);
	
	for (int i = 0; i < n; i++) {
		ind[g[i].first] = i;
	}

	for (int i = 0; i < n; i++) {
		g2[i].first = g[i].first;
		for (int j = 0; j < (int)g[i].second.size(); j++) {
			if (i > ind[g[i].second[j].v]) {
				g2[i].second.push_back(g[i].second[j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int a = g2[i].first;
		for (auto b : g2[i].second) {
			mark[b.v] = b.ind;
		}
		for (auto b : g2[i].second) {
			if (ind[a] > ind[b.v]) {
				for (auto c : g2[ind[b.v]].second) {
					if (ind[b.v] > ind[c.v] && mark[c.v] != 0) {
						add(b.ind);
						add(c.ind);
						add(mark[c.v]);
					}
				}
			}
		}
		for (auto b : g2[i].second) {
			mark[b.v] = 0;
		}
	}
	print_ans();
	return 0;
}