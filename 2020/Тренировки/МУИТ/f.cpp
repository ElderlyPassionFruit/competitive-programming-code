#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;
vector<pair<int, int>> a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(all(a));
}
 
vector<int> pref, suff;

void build() {
	pref.resize(n), suff.resize(n);
	for (int i = 1; i < pref.size(); i += 2) {
		if (i - 2 > 0) pref[i] = pref[i - 2];
		pref[i] += a[i - 1].first;
	}
	for (int i = suff.size() - 2; i >= 0; i -= 2) {
		if (i + 2 < suff.size()) suff[i] = suff[i + 2];
		suff[i] += a[i].first;
	}
	/*cout << "pref = " << endl;
	for (auto i : pref)
		cout << i << " ";
	cout << endl;
	cout << "suff = " << endl;
	for (auto i : suff)
		cout << i << " ";
	cout << endl;*/
}

vector<int> ans;

int get(int pos) {
	if (pos % 2 == 0) {
		int ans = 0;
		if (pos + 1 < n) ans += suff[pos + 1];
		if (pos - 1 >= 0) ans += pref[pos - 1];
		return ans;
	} else {
		int ans = 0;
		if (pos + 2 < n) ans += suff[pos + 2];
		if (pos - 2 >= 0) ans += pref[pos - 2];
		ans += a[pos - 1].first;
		return ans;
	}
}

void run() {
	build();
	ans.resize(n);
	for (int i = 0; i < n; i++) {
		ans[a[i].second] = get(i);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << " ";
	}
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