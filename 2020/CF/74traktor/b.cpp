#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

map<int, int> cnt;
bool ans = false;

set<pair<int, int>> have;

void relax() {
	bool square = false;
	int rect = 0;
	ans = false;
	for (auto i : have) {
		int now = -i.first;
		if (now < 2) return;
		if (!square && now < 4) return;
		if (!square) {
			square = true;
			now -= 4;
		} 
		rect += now / 2;
		ans = square && (rect >= 2);
		if (ans) break;
	}
}

void add(int x) {
	if (cnt.count(x)) have.erase({-cnt[x], x});
	cnt[x]++;
	have.insert({-cnt[x], x});
	relax();
}

void del(int x) {
	if (cnt.count(x)) have.erase({-cnt[x], x});
	cnt[x]--;
	have.insert({-cnt[x], x});
	relax();
}

void wr() {
	cout << "have = " << endl;
	for (auto i : have) {
		cout << i.first << " " << i.second << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		add(x);
	}
	int q;
	cin >> q;
	while (q--) {
		char a;
		int x;
		cin >> a >> x;
		if (a == '+') add(x);
		else del(x);
		cout << (ans ? "YES\n" : "NO\n");
	}
	return 0;
}