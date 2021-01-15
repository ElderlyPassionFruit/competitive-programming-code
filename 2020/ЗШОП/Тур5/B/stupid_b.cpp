#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

const int MAXN = 1000 + 10;
int n;
vector<int> g[MAXN];
string s;

void read() {
	cin >> n;
	cin >> s;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
}

bool check(int l, int r, string s) {
	int bal = 0;
	for (int i = l; i <= r; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal < 0) return false;
	}
	return bal == 0;
}

int calc(string s) {
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		for (int j = i + 1; j < s.size(); j++) {
			ans += check(i, j, s);
		}
	}
	return ans;
}

int ans;

void dfs(int v, string t, int fans) {
	t += s[v];
	fans = calc(t);
	cerr << "v = " << v << " fans = " << fans << " t = " << t << endl;
	ans = ans ^ ((v + 1) * fans);
	for (auto i : g[v])
		dfs(i, t, fans);
}

void run() {
	ans = 0;
	dfs(0, "", 0);
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

