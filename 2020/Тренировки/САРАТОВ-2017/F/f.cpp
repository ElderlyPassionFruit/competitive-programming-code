#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
int n, m;

pair<char, char> ans[MAXN];

bool ch[MAXN];
int sex[MAXN];
int nxt[MAXN];
int mom[MAXN];
int dad[MAXN];

vector<pair<int, int>> g[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	fill(sex, sex + n, -1);
	fill(nxt, nxt + n, -1);
	fill(mom, mom + n, -1);
	fill(dad, dad + n, -1);
	fill(ch, ch + n, 0);
	for (int i = 0; i < m; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		x--;
		y--;
		g[x].push_back({y, t});
	}

	for (int it = 0; it < 20; it++) {
		queue<int> q;
		for (int i = 0; i < n; i++) {
			q.push(i);
		}

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto [to, type] : g[v]) {
				if (type == 1) {
					mom[v] = to;
					if (sex[to] == -1) {
						sex[to] = 0;
						q.push(to);
					}
					if (ch[to] == 0) {
						ch[to] = 1;
						q.push(to);
					} 
				} else if (type == 2) {
					dad[v] = to;
					if (sex[to] == -1) {
						sex[to] = 1;
						q.push(to);
					}
					if (ch[to] == 0) {
						ch[to] = 1;
						q.push(to);
					} 
				} else if (type == 3) {
					if (sex[to] == 0) mom[v] = to;
					if (sex[to] == 1) dad[v] = to;
					if (mom[v] != -1 && mom[v] != to) dad[v] = to;
					if (dad[v] != -1 && dad[v] != to) mom[v] = to;
					if (sex[to] == -1) {
						if (mom[v] == to) {
							sex[to] = 0;
							q.push(to);
						} 
						if (dad[v] == to) {
							sex[to] = 1;
							q.push(to);
						}
					}
					if (ch[to] == 0) {
						ch[to] = 1;
						q.push(to);
					}
				} else if (type == 4) {
					nxt[v] = to;
					if (nxt[to] == -1) {
						nxt[to] = v;
						q.push(to);
					}
				}
			}
			if (mom[v] != -1 && dad[v] != -1) {
				if (nxt[mom[v]] == -1) {
					nxt[mom[v]] = dad[v];
					q.push(mom[v]);
				}
				if (nxt[dad[v]] == -1) {
					nxt[dad[v]] = mom[v];
					q.push(dad[v]);
				}
			}
			int to = nxt[v];
			if (to != -1) {
				if (nxt[to] == -1) {
					nxt[to] = v;
					q.push(to);
				}
				if (ch[to] != ch[v]) {
					ch[to] = ch[v] = 1;
					q.push(to);
					q.push(v);
				}
				if (sex[to] == -1 && sex[v] != -1) {
					sex[to] = sex[v] ^ 1;
					q.push(to);
				}
				if (sex[to] != -1 && sex[v] == -1) {
					sex[v] = sex[to] ^ 1;
					q.push(v);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (sex[i] == -1) {
			ans[i].first = '?';
		} else if (sex[i] == 0) {
			ans[i].first = 'f';
		} else {
			ans[i].first = 'm';
		}
		if (ch[i]) {
			ans[i].second = '+';
		} else {
			ans[i].second = '-';
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i].first << " " << ans[i].second << "\n";
	}
	return 0;
}