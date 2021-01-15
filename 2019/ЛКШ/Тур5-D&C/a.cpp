#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int s, f, u, v;
	event(int a, int b, int c, int d) {
		s = a, f = b, u = c, v = d;
	}
};

int n, q;
vector<event> ed;	
vector<pair <int, int> > query;
void read() {
	cin >> n >> q;

	map <pair <int, int>, int> start;

	for (int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '?') {
			query.push_back({i, query.size()});
		}
		if (type == '+') {
			int u, v;
			cin >> u >> v;
			if (u > v) {
				swap(u, v);
			}
			start[{u, v}] = i;
		}
		if (type == '-') {
			int u, v;
			cin >> u >> v;
			if (u > v) {
				swap(u, v);
			}
			ed.push_back(event(start[{u, v}], i + 1, u, v));
			start[{u, v}] = -1;
		}
	}

	for (auto i : start) {
		if (i.second != -1) {
			ed.push_back(event(i.second, q + 1, i.first.first, i.first.second));
		}
	}
}

const int MAXN = 3e5 + 10;
int par[MAXN], sz[MAXN];
int cnt;
vector <pair <int, int> > st;

void make() {
	cnt = n;
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		sz[i] = 1;
	}
}

int get_par(int v) {
	if (v == par[v]) 
		return v;
	return get_par(par[v]);
}

void union_set(int v, int u) {
	if (sz[v] < sz[u])
		swap(v, u);
	par[u] = v;
	sz[v] += sz[u];
	st.push_back({u, v});
	cnt--;
}

void undo() {
	assert(st.size() > 0);
	int u = st.back().first;
	int v = st.back().second;
	st.pop_back();
	par[u] = u;
	sz[v] -= sz[u];
	cnt++;
}

int get_ans() {
	return cnt;
}

vector<int> ans;

void solve(int l, int r, vector<event> a, vector<pair <int, int> > query) {
	if (l == r - 1) {
		int op = 0;
		for (auto i : a) {
			if (i.s >= r || i.f <= l) 
				continue;
			if (i.s <= l && i.f >= r) {
				int u = get_par(i.u);
				int v = get_par(i.v);
				if (u != v) {
					union_set(u, v);
					op++;
				}
			}
		}

		for (auto i : query) {
			if (i.first == l) {
				ans[i.second] = get_ans(); 
			}
		}

		while (op--) {
			undo();
		}
		return;
	}

	vector<event> down;
	int op = 0;
	for (auto i : a) {
		if (i.s >= r || i.f <= l) 
			continue;
		if (i.s <= l && i.f >= r) {
			int u = get_par(i.u);
			int v = get_par(i.v);
			if (u != v) {
				union_set(u, v);
				op++;
			}
		}
		else {
			down.push_back(i);
		}
	}

	vector<pair <int, int> > q_l, q_r;
	int m = (l + r) / 2;
	for (auto i : query) {
		if (i.first < m) {
			q_l.push_back(i);
		}
		else {
			q_r.push_back(i);
		}
	}

	solve(l, m, down, q_l);
	solve(m, r, down, q_r);

	while (op--) {
		undo();
	}
}

void run() {
	make();
	ans.resize(query.size());
	solve(0, q + 1, ed, query);
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
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