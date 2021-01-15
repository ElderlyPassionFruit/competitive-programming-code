#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ull
int n;

void read() {
	cin >> n;
}

bool check(int x) {
	int s = x;
	int sum = 0;
	while (s) {
		sum += s % 10;
		if (s % 10 == 0) return false;
		s /= 10;
		if (x % sum != 0) return false;
	}
	return true;
}

int get_len(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

void run() {
	int x = 1 << n;
	cout << x << endl;
	map<int, int> ans;
	for (int i = 1; i < 1e9; i++) {
		int nxt = x * i;
		if (check(nxt)) {
			ans[get_len(nxt)] = nxt;
			//cout << nxt << " " << get_len(nxt) << endl;
		}
	}
	for (auto i : ans)
		cout << i.first << " " << i.second << endl;
}

void write() {

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