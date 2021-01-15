#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, x, y;

void read() {
	cin >> n >> x >> y;
}

int calc(int a, int b) {
	int ans = abs(a - b);
	chkmin(ans, abs(a - x) + abs(b - y) + 1);
	chkmin(ans, abs(a - y) + abs(b - x) + 1);
	return ans;
}

vector<int> ans;

void run() {
	ans.resize(n - 1);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			ans[calc(i, j) - 1]++;
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
	//cout << endl;
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