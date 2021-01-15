#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 2e6 + 10;
bool p[MAXN];

int nxtL[MAXN], nxtR[MAXN];

void build() {
	for (int i = 2; i < MAXN; i++)
		p[i] = true;
	for (int i = 2; i < MAXN; i++) {
		if (p[i]) {
			for (int j = i + i; j < MAXN; j += i) {
				p[j] = false;
			}
		}
	}

	int last = -1e9;
	for (int i = 0; i < MAXN; i++) {
		if (p[i])
			last = i;
		nxtL[i] = last;
	}
	last = -1e9;
	for (int i = MAXN - 1; i >= 0; i--) {
		if (p[i])
			last = i;
		nxtR[i] = last;
	}
}

int n, m;
vector<int> a;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int get_cost(int i) {
	return min(abs(a[i] - 2), abs(a[i] - 3));
}

vector<pair<int, int>> ans;

void no() {
	cout << "NO\n";
	exit(0);
}

void run() {
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (get_cost(i) < get_cost(pos))
			pos = i;
	}
	ans.resize(n);
	for (int i = 0; i < n; i++) {
		if (pos == i) continue;
		int x = abs(nxtL[a[i]] - a[i]);
		int y = abs(nxtR[a[i]] - a[i]);
		if (x < y) {
			ans[i] = {x, 0};
		}
		else {
			ans[i] = {0, y};
		}
		m -= min(x, y);
	}

	if (m < 0) no();
	if (get_cost(pos) > m) {
		int x = abs(nxtL[a[pos]] - a[pos]);
		int y = abs(nxtR[a[pos]] - a[pos]);
		if (x < y) {
			ans[pos] = {x, 0};
		}
		else {
			ans[pos] = {0, y};
		}
		m -= min(x, y);	
		if (m < 0) no();
		if (m % 2) no();
		ans[0].first += m / 2;
		ans[0].second += m / 2;
	}
	else {
		int x = abs(a[pos] - 2);
		int y = abs(a[pos] - 3);
		if (x < y) {
			m -= x;
			if (a[pos] >= 2)
				ans[pos] = {x + m / 2, (m + 1) / 2};
			else
				ans[pos] = {m / 2, (m + 1) / 2 + x}; 
		}
		else {
			m -= y;
			if (a[pos] < 3) 
				ans[pos] = {(m + 1) / 2, y + m / 2};
			else
				ans[pos] = {y + (m + 1) / 2, m / 2};
		}
	}
}

void write() {
	cout << "YES\n";
	for (auto i : ans)
		cout << i.first << " " << i.second << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	/*cout << "p = " << endl;
	for (int i = 0; i < 20; i++)
		cout << i << " " << p[i] << endl;
	cout << "nxt = " << endl;
	for (int i = 0; i < 20; i++) {
		cout << i << " " << nxtL[i] << " " << nxtR[i] << endl;
	}*/
	read();
	run();
	write();
	return 0;
}