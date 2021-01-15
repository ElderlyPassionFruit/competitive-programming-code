#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> p, b;

void read() {
	cin >> n;
	p.resize(n);
	for (auto &i : p){
		cin >> i;
		i--;
	}
	b.resize(n);
	for (auto &i : b)
		cin >> i;
}

vector<bool> used;

void dfs(int v) {
	used[v] = true;
	if (used[p[v]])
		return;
	dfs(p[v]);
}

int cnt_cycles() {
	int ans = 0;
	used.assign(n, false);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
			ans++;
		}
	}
	return ans;
}

int cnt_one() {
	int ans = 0;
	for (auto i : b)
		ans += i;
	return ans;
}

int cnt_len_one() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (p[i] == i)
			ans++;
	}
	return ans;
}

int ans = 0;

void run() {
	ans = (1 - (cnt_one() % 2));
	
	int cycles = cnt_cycles();
	if (cycles > 1)
		ans += cycles;
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