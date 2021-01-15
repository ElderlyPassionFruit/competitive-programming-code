#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;

void read() {
	cin >> n >> m;
	if (n > m) swap(n, m);
}

struct state{
	int mask;
	ll cnt;
	state() {}
	state(int a, ll b) {
		mask = a, cnt = b;
	}
};

bool operator<(const state & a, const state & b) {
	return tie(a.mask, a.cnt) < tie(b.mask, b.cnt);
}

void make(vector<state> & a) {
	sort(all(a));
	vector<state> ans;
	for (auto i : a) {
		if (ans.empty() || ans[ans.size() - 1].mask != i.mask)
			ans.push_back(i);
		else
			ans[ans.size() - 1].cnt += i.cnt;
	}
	a = ans;
}

int get_bit(int mask, int pos) {
	return (mask >> pos) & 1;
}

bool check(int mask, int pos) {
	if (pos == n - 1) return true;
	vector<int> need = {0, 1, n, n + 1};
	int fans = 0;
	for (auto i : need)
		fans += get_bit(mask, i);
	return fans != 0 && fans != 4;
}	

void add(vector<state> & ans, const state & mask, int x, int pos) {
	if (!check(mask.mask | x, pos)) return;
	ans.push_back({(mask.mask | x) >> 1, mask.cnt});
}

void calc(vector<state> & ans, const state & mask, int pos) {
	add(ans, mask, 1 << (n + 1), pos);
	add(ans, mask, 0, pos);
}

void solve(vector<state> & mask) {
	vector<state> ans;
	for (int i = 0; i < n; i++) {
		for (auto j : mask) {
			calc(ans, j, i);
		}
		mask = ans;
		make(mask);
		ans.clear();
	}
}

ll ans = 0;
vector<state> mask;
void run() {
	for (int i = 0; i < (1 << n); i++)
		mask.push_back({i, 1});
	for (int i = 0; i < m - 1; i++) {
		solve(mask);
	}
	for (auto i : mask)
		ans += i.cnt;
}

void write() {
	cout << ans << endl;
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