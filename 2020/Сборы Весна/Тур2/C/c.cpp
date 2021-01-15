#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool check(int a, int b, int x) {
	return a <= x && b >= x;
}

bool check(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return check(a, b, c) || check(a, b, d) || check(c, d, a) || check(c, d, b);
}

bool check(pt a, pt b, pt c, pt d) {
	bool ans = check(a.x, b.x, c.x, d.x) && check(a.y, b.y, c.y, d.y);
	return ans;
}

struct event{
	int pos, type, ind;
	event() {}
	event(int _pos, int _type) {
		pos = _pos, type = _type;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.pos, a.type) < tie(b.pos, b.type);
}

void add(set<event> & a, event s, event f) {
	while (true) {
		auto it = a.lower_bound(event(s.pos, 0));
		if (it == a.end()) break;
		if (it->pos > f.pos) break;
		a.erase(it); 
	}
	auto it = a.lower_bound(event(s.pos, 0));
	if (it == a.end() || it->type == 1) a.insert(f);
	it = a.lower_bound(event(s.pos, 0));
	if (it == a.begin() || (--it)->type == 2) a.insert(s);
}

bool check(set<event> & a, int x) {
	auto it = a.lower_bound(event(x, 2));
	if (it == a.end()) return false;
	return it->type == 2;
}

struct segment_tree_check{
	vector<set<event>> tree;
	vector<int> pos;
	int n;
	segment_tree_check() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree_check(int sz) {
		n = sz;
		tree.resize(4 * n);
		pos.resize(n);
		build(1, 0, n);
	}

	bool get(int v, int tl, int tr, int l, int r, int x) {
		if (tl >= r || tr <= l) return false;
		if (tl >= l && tr <= r) {
			return check(tree[v], x);
		}
		int tm = (tl + tr) / 2;
		if (get(v * 2, tl, tm, l, r, x)) return true;
		return get(v * 2 + 1, tm, tr, l, r, x);
	}

	bool get(int l, int r, int x) {
		return get(1, 0, n, l, r + 1, x);
	}

	void upd(int v, int l, int r) {
		v = pos[v];
		while (v) {
			add(tree[v], event(l, 1), event(r, 2));
			v /= 2;
		}
	}
};

struct segment{
	int l, r, ind;
	segment() {}
	segment(int _l, int _r, int _ind) {
		l = _l, r = _r, ind = _ind;
	}
};

bool operator<(const segment & a, const segment & b) {
	return tie(a.l, a.r, a.ind) < tie(b.l, b.r, b.ind);
}

void add(set<segment> & a, int l, int r, int ind) {
	a.insert(segment(l, r, ind));
}

/*vector<segment> ntree;
vector<int> ans;
for (auto [tl, tr, ind] : tree[v]) {
	if (!check(tl, tr, x)) {
		ntree.push_back({tl, tr, ind});
		continue;
	}
	ans.push_back(ind);
}
tree[v] = ntree;
return ans;*/

vector<int> calc(set<segment> & a, int x) {
	set<segment> New;
	vector<int> ans;
	for (auto [tl, tr, ind] : a) {
		if (tl <= x && tr >= x) {
			ans.push_back(ind);
		} else {
			New.insert({tl, tr, ind});
		}
	}
	a = New;
	return ans;
}

struct segment_tree_del{
	vector<set<segment>> tree;
	vector<int> pos;
	int n;

	segment_tree_del() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree_del(int sz) {
		n = sz;
		tree.resize(4 * n);
		pos.resize(n);
		build(1, 0, n);
	}

	vector<int> get(int v, int tl, int tr, int l, int r, int x) {
		if (tl >= r || tr <= l) return {};
		if (tl >= l && tr <= r) {
			return calc(tree[v], x);
		}
		int tm = (tl + tr) / 2;
		vector<int> L = get(v * 2, tl, tm, l, r, x);
		vector<int> R = get(v * 2 + 1, tm, tr, l, r, x);
		for (auto i : R) L.push_back(i);
		return L;
	}

	vector<int> get(int l, int r, int x) {
		return get(1, 0, n, l, r + 1, x);
	}

	void upd(int v, int l, int r, int ind) {
		v = pos[v];
		while (v) {
			//tree[v].push_back({l, r, ind});
			add(tree[v], l, r, ind);
			v /= 2;
		}
	}
};

const int MAXN = 1e5 + 10;
int n;
vector<int> x[MAXN], y[MAXN];
vector<pt> a;
segment_tree_check H, W;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.x >> i.y;
	}
	for (int i = 0; i < n; i++) {
		x[a[i].x].push_back(i);
		y[a[i].y].push_back(i);
	}
}

void no() {
	cout << "NE\n";
	exit(0);
}

vector<int> used;
vector<pair<int, int>> ans;

bool check(pair<int, int> have) {
	int u = have.first, v = have.second;
	bool fans;
	if (a[u].x == a[v].x) {
		int l = a[u].y, r = a[v].y;
		int x = a[u].x;
		if (l > r) swap(l, r);
		fans = !W.get(l, r, x);
	} else {
		int l = a[u].x, r = a[v].x;
		int x = a[u].y;
		if (l > r) swap(l, r);
		fans = !H.get(l, r, x);
	}
	return fans;
}

void add(pair<int, int> have) {
	if (!check(have)) no();
	int u = have.first, v = have.second;
	if (a[u].x == a[v].x) {
		int l = a[u].y, r = a[v].y;
		int x = a[u].x;
		if (l > r) swap(l, r);
		H.upd(x, l, r);
	} else {
		int l = a[u].x, r = a[v].x;
		int x = a[u].y;
		if (l > r) swap(l, r);
		W.upd(x, l, r);
	}
	ans.push_back(have);
}

vector<int> now;

void dfs(int id) {
	used[id] = true;
	now.push_back(id);
	for (auto a1 : x[a[id].x]) {
		if (a1 != id && !used[a1]) {
			dfs(a1);
		}
	}
	for (auto a1 : y[a[id].y]) {
		if (a1 != id && !used[a1]) {
			dfs(a1);
		}
	}
}

queue<pair<int, int>> q;

vector<vector<int>> cycles;
segment_tree_del haveH, haveW;

void add_del(pair<int, int> have, int ind) {
	int u = have.first;
	int v = have.second;
	if (a[u].x == a[v].x) {
		int l = a[u].y, r = a[v].y;
		int x = a[u].x;
		if (l > r) swap(l, r);
		haveH.upd(x, l, r, ind);
	} else {
		int l = a[u].x, r = a[v].x;
		int x = a[u].y;
		if (l > r) swap(l, r);
		haveW.upd(x, l, r, ind);
	}
}

void build() {
	used.assign(n, 0);
	for (int i = 0; i < n; i++) {
		if (x[a[i].x].size() == 1 && y[a[i].y].size() == 1) {
			no();
		}
	}
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if ((x[a[i].x].size() - 1 + y[a[i].y].size() - 1) % 2 == 0) continue;
		now.clear();
		if (x[a[i].x].size() == 1) dfs(x[a[i].x][0]);
		else dfs(y[a[i].y][0]);
		if (now.size() % 2 == 1) no();
		for (int j = 0; (int)j < now.size(); j += 2) {
			q.push({now[j], now[j + 1]});
		}
	}
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if (x[a[i].x].size() != 2 || y[a[i].y].size() != 2) continue;
		now.clear();
		dfs(x[a[i].x][0]);
		if (now.size() % 2 == 1) no();
		if (a[now[0]].x != a[now[1]].x) {
			now.push_back(now[0]);
			now.erase(now.begin());
		}
		cycles.push_back(now);
	}
	for (auto i : used)
		assert(i);
}

vector<pair<int, int>> get_del(pair<int, int> have) {
	int u = have.first;
	int v = have.second;
	vector<pair<int, int>> ans;
	if (a[u].x == a[v].x) {
		int l = a[u].y, r = a[v].y;
		int x = a[u].x;
		if (l > r) swap(l, r);
		auto fans = haveW.get(l, r, x);
		for (auto i : fans) {
			ans.push_back({i, 1});
		}
	} else {
		int l = a[u].x, r = a[v].x;
		int x = a[u].y;
		if (l > r) swap(l, r);
		auto fans = haveH.get(l, r, x);
		for (auto i : fans) {
			ans.push_back({i, 2});
		}
	}
	return ans;
}

void Sort(vector<int> & cycle, int type) {
	if (type == 1) {
		sort(all(cycle), [&] (int i, int j) {return a[i].x < a[j].x;});
	} else {		
		sort(all(cycle), [&] (int i, int j) {return a[i].y < a[j].y;});
	}
}

void run() {
	build();
	H = segment_tree_check(MAXN);
	W = segment_tree_check(MAXN);
	haveH = segment_tree_del(MAXN);
	haveW = segment_tree_del(MAXN);
	vector<int> my_ind(n);

	for (int i = 0; i < (int)cycles.size(); i++) {
		int sz = cycles[i].size();
		for (int type = 1; type <= 2; type++) {
			Sort(cycles[i], type);
			for (int j = 0; j < sz; j += 2) {
				add_del({cycles[i][j], cycles[i][(j + 1) % sz]}, i);
				my_ind[cycles[i][j]] = i;
			}
		}
	}
	used.assign((int)cycles.size(), 0);

	while (!q.empty()) {
		int u = q.front().first;
		int v = q.front().second;
		q.pop();
		add({u, v});
		auto fdel = get_del({u, v});
		for (auto [ind, type] : fdel) {
			if (used[ind]) {
				if (used[ind] == type) continue;
				no();
			}
			used[ind] = type;
			Sort(cycles[ind], type);
			int sz = cycles[ind].size();
			for (int i = 0; i < sz; i += 2) {
				int u = cycles[ind][i % sz];
				int v = cycles[ind][(i + 1) % sz];
				q.push({u, v});
			}
		}
	}
	for (int i = 0; i < (int)cycles.size(); i++) {	
		if (used[i]) continue;
		Sort(cycles[i], 1);
		for (int j = 0; j < (int) cycles[i].size(); j += 2) {
			add({cycles[i][j], cycles[i][(j + 1) % (int)cycles[i].size()]});
		}
	}
}

void write() {
	cout << "DA\n";
	for (auto i : ans)
		cout << i.first + 1 << " " << i.second + 1 << "\n";
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

/*
8
3 1
5 6
7 3
2 2
8 7
3 7
5 5
1 3



*/