#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k, c;
string s;

void read() {
	cin >> n >> k >> c;
	cin >> s;
}

const int MAXN = 2e5 + 10;

int pref[MAXN], suff[MAXN];

void build() {
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1];
		if (s[i - 1] == 'o') {
			chkmax(pref[i], 1);
			if (i - c - 1 >= 1) {
				chkmax(pref[i], pref[i - c - 1] + 1);
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		suff[i] = suff[i + 1];
		if (s[i - 1] == 'o') {
			chkmax(suff[i], 1);
			if (i + c + 1 <= n) {
				chkmax(suff[i], suff[i + c + 1] + 1);
			}
		}
	}
}

deque<pair<int, int>> q;

void add(int x, int ind) {
	while (!q.empty() && q.back().first <= x)
		q.pop_back();
	q.push_back({x, ind});
}

void del(int ind) {
	if (q.front().second == ind)
		q.pop_front();
}

int get() {
	if (q.empty()) return 0;
	return q.back().first;
}

void upd(int pos) {
	if (pos - c - 1)
}

bool check(int pos) {
	if (s[pos - 1] == 'x') return false;
	if (pref[pos - 1] >= k) return false;
	if (suff[pos + 1] >= k) return false;
	for (int i = pos - 1; i >= max(1, pos - c - 1); i--) {
		int nxt = max(i + c + 1, pos + 1);
		if (nxt > n) continue;
		if (pref[i] + suff[nxt] >= k) return false;
	}
	return true;
}

void run() {
	build();
	for (int i = 1; i <= n; i++) {
		upd(i);
		if (check(i)) {
			cout << i << "\n";
		}
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