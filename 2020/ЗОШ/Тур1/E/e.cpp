#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int a[MAXN][4];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a[i][j];
		}
	}
}

struct event{
	int cost, pos;
	event() {}
	event(int a, int b) {
		cost = a, pos = b;
	}
};	

bool operator<(const event & i, const event & j) {
	return tie(i.cost, a[j.pos][3]) < tie(j.cost, a[i.pos][3]);
}

set<event> have;

set<int> color[3];
map<int, int> cnt[3];
const int MAXC = 500;
set<int> Now[3][MAXC];

void add_color(int pos, int c) {
	color[c].insert(a[pos][c]);
	color[c].insert(a[pos][c] + 360);
	color[c].insert(a[pos][c] - 360);
	cnt[c][a[pos][c]]++;
	cnt[c][a[pos][c] + 360]++;
	cnt[c][a[pos][c] - 360]++;
	Now[c][a[pos][c]].insert(pos);
}

void add_pos(int pos) {
	for (int i = 0; i < 3; i++)
		add_color(pos, i);
}

int Get(int pos, int c) {
	if (cnt[c][a[pos][c]] != 1) return 0;
	return *(color[c].lower_bound(a[pos][c] + 1)) - *(--color[c].lower_bound(a[pos][c]));
}

int get_cost(int pos) {
	int ans = 0;
	for (int i = 0; i < 3; i++)
		ans += Get(pos, i);
	return ans;
}

void build() {
	for (int i = 0; i < n; i++)
		add_pos(i);
	for (int i = 0; i < n; i++)
		have.insert(event(get_cost(i), i));
}

void del_color(int pos, int c) {
	if (cnt[c][a[pos][c]] == 1)
	color[c].erase(a[pos][c]);
	if (cnt[c][a[pos][c] + 360] == 1)
	color[c].erase(a[pos][c] + 360);
	if (cnt[c][a[pos][c] - 360] == 1)
	color[c].erase(a[pos][c] - 360);
	cnt[c][a[pos][c]]--;
	cnt[c][a[pos][c] + 360]--;
	cnt[c][a[pos][c] - 360]--;
	Now[c][a[pos][c]].erase(pos);
}

void del_pos(int pos) {
	for (int i = 0; i < 3; i++)
		del_color(pos, i);
}

int make(int x) {
	return ((x % 360) + 360) % 360;
}

vector<int> frecalc(int pos, int c) {
	vector<int> ans;
	auto it = color[c].lower_bound(a[pos][c]);
	if (it != color[c].end()) {
		int x = *it;
		x = make(x);
		if ((int)Now[c][x].size() == 1) {
			ans.push_back(*Now[c][x].begin());
		}
	}
	if (it != color[c].begin()) {
		--it;
		int x = *it;
		x = make(x);
		if ((int)Now[c][x].size() == 1) {
			ans.push_back(*Now[c][x].begin());
		}
	}
	return ans;
}

void del(event x) {
	vector<int> recalc;
	have.erase(x);
	del_pos(x.pos);
	for (int i = 0; i < 3; i++) {
		auto help = frecalc(x.pos, i);
		for (auto j : help) {
			recalc.push_back(j);
		}
	}
	sort(all(recalc));
	recalc.resize(unique(all(recalc)) - recalc.begin());
	add_pos(x.pos);
	for (auto i : recalc) {
		have.erase(event(get_cost(i), i));
	}
	del_pos(x.pos);
	for (auto i : recalc) {
		have.insert(event(get_cost(i), i));
	}
}

vector<int> ans;

void run() {
	build();
	while (!have.empty()) {
		auto x = *have.begin();
		del(x);
		ans.push_back(a[x.pos][3]);
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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