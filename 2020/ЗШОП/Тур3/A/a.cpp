#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<pair<int, int> > a;
vector<int> b;

void read() {
	cin >> n;
	a.resize(n + 1);
	for (int i = 0; i < n + 1; i++) {
		cin >> a[i].first;
		a[i].second = i;
	} 
	sort(all(a));
	b.resize(n);
	for (auto &i : b)
		cin >> i;
	sort(all(b));
}

vector<int> pref, suff;

void build() {
	for (int i = 0; i < n; i++) {
		pref.push_back(max(0, a[i].first - b[i]));
	}
	for (int i = 1; i < n; i++)
		chkmax(pref[i], pref[i - 1]);
	for (int i = n; i >= 1; i--) {
		suff.push_back(max(0, a[i].first - b[i - 1]));
	}
	for (int i = 1; i < n; i++)
		chkmax(suff[i], suff[i - 1]);
	reverse(all(suff));
}

int calc(int pos) {
	int ans = 0;
	if (pos > 0) chkmax(ans, pref[pos - 1]);
	if (pos < n) chkmax(ans, suff[pos]);
	return ans;
}

vector<int> ans;

void run() {
	build();
	ans.resize(n + 1);
	for (int i = 0; i < n + 1; i++) 
		ans[a[i].second] = calc(i);
}

void write() {
	for (auto i : ans)
		cout << i << " ";
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