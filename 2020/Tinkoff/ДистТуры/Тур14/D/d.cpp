#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e5 + 10;
int n, m;
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int solve(int l, int r) {
	int ans = 0;
	for (int x = l; x <= r; x++) {
		for (int y = x + 1; y <= r; y++) {
			for (int z = y + y - x; z <= r; z++) {
				chkmax(ans, a[x] + a[y] + a[z]);
			}
		}
	}
	return ans;
}

vector<int> ans;

void run() {
	cin >> m;
	while (m--) {
		int l, r;
		cin >> l;
		cin >> r;
		l--;
		r--;
		ans.push_back(solve(l, r));
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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