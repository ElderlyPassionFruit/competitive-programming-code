#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<int> a;
void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

bool check(int x) {
	int have = 0;
	for (int i = 0; i < n; i++) {
		if (have >= a[i])
			have++;
		else {
			if (x > 0) {
				x--;
				have++;
			}
		}
	}
	return have >= m;
}

int ans;

void run() {
	int l = -1, r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
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