#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;

int n;
vector<int> g[MAXN];
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans;

void run() {
	multiset<int> have;
	for (int i = 0; i < n; i++)
		have.insert(a[i]);
	//cout << "a = " << endl;
	//for (int i = 0; i < n; i++)
	//	cout << a[i] << " ";
	//cout << endl;
	have.insert(-1e9 - 10);
	ans = 1e9 + 10;

	for (int i = 0; i < n; i++) {
		//cout << "have = " << endl;
		//for (auto j : have)
		//	cout << j << " ";
		//cout << endl;
		//cout << "puhh" << endl;
		int fans = a[i];
		have.erase(have.find(a[i]));
		for (auto j : g[i]) {
			assert(have.find(a[j]) != have.end());
			have.erase(have.find(a[j]));
			chkmax(fans, a[j] + 1);
		}

		assert(!have.empty());
		chkmax(fans, 2 + (*(--have.end())));
		
		chkmin(ans, fans);
		have.insert(a[i]);
		for (auto j : g[i]) {
			have.insert(a[j]);
		}
	}
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