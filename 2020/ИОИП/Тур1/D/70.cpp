#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;
int p[MAXN];
vector<int> g[MAXN];
bool used[MAXN];
int n, k;

void read() {
	cin >> n >> k;
	p[0] = -1;
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
		g[p[i]].push_back(i);
	}
}

int get_h(int v) {
	if (used[v]) return 0;
	int ans = 0;
	while (v != -1) {
		ans++;
		v = p[v];
	}
	return ans;
}

void del(int v) {
	while (v != -1) {
		for (auto i : g[v]) {
			p[i] = -1;
		}
		used[v] = true;
		v = p[v];
	}
}

int ans;

void run() {
	ans = 0;
	for (int i = 0; i < k; i++) {
		int best = 0;
		for (int j = 0; j < n; j++)
			if (get_h(j) > get_h(best))
				best = j;
		if (get_h(best) == 0) break;
		ans += get_h(best);
		del(best);
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
