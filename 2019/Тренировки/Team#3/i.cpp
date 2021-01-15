#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

map <pair <int, int>, int> used;

int query(int u, int v) {
	if (u == v)
		return 0;
	if (u > v)
		swap(u, v);
	if (used.count({u, v}))
		return used[{u, v}];

	cout << "? " << u + 1 << " " << v + 1 << endl;
	int ans;
	cin >> ans;
	used[{u, v}] = ans;
	return ans;
} 

int n;

void read() {
	cin >> n;
}

struct event{
	int u, dist;
};

int find_root() {
	pair <int, int> help = {0, 0};
	for (int i = 1; i < n; i++) {
		chkmax(help, make_pair(query(0, i), i));
	}	
	pair <int, int> ans = {0, 0};
	vector<event> have1;
	for (int i = 0; i < n; i++) {
		pair <int, int> x;
		x = make_pair(query(help.second, i), i);
		chkmax(ans, x);
		have1.push_back({x.second, x.first});
	}

	vector<event> have2;
	for (int i = 0; i < n; i++) {
		pair <int, int> x;
		x = make_pair(query(ans.second, i), i);
		have2.push_back({x.second, x.first});
	}

	/*cout << "have1 = " << endl;
	for (auto i : have1) {
		cout << i.u << " " << i.dist << endl;
	}

	cout << "have2 = " << endl;
	for (auto i : have2) {
		cout << i.u << " " << i.dist << endl;
	}*/

	int lg = log2(n);
	//cout << "lg = " << lg << endl;
	for (auto i : have1) {
		for (auto j : have2) {
			if (i.u == j.u && i.dist == lg && j.dist == lg)
				return i.u;
		}
	}
	assert(false);
}

vector<int> ans;

void solve(int v, vector<event> g) {
	//cout << "v = " << v << endl;
	if (g.size() == 1)
		return;
	int L = -1, R = -1;
	for (auto i : g) {
		if (i.dist == 1) {
			if (L == -1)
				L = i.u;
			else
				R = i.u;
		}
	}

	ans[L] = v;
	ans[R] = v;

	vector<event> l, r;
	l.push_back({L, 0});
	r.push_back({R, 0});
	for (auto i : g) {
		if (i.u == v)
			continue;
		if (i.u == L)
			continue;
		if (i.u == R)
			continue;
		int d = query(i.u, L);
		if (d < i.dist) {
			l.push_back({i.u, d});
		}
		else {
			r.push_back({i.u, i.dist - 1});
		}
	}
	solve(L, l);
	solve(R, r);
}

void run() {
	ans.resize(n, -1);
	int root = find_root();
	//cout << "root = " << root << endl;
	vector<event> x;
	x.push_back({root, 0});
	for (int i = 0; i < n; i++) {
		if (i == root) continue;
		x.push_back({i, query(i, root)});
	}
	solve(root, x);
}

void write() {
	cout << "! ";
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << endl;
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