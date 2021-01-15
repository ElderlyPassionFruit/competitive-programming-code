#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		char x;
		cin >> x;
		a[i] = x - '0';
	}
}

vector<int> ans;
vector<bool> used;
void run() {
	ans = a;
	used.assign(n, false);
	bool flag = true;
	for (int i = 0; i < k; i++) {
		for (int j = i; j < n; j += k) {
			flag &= ans[j] <= ans[i];
		}
	}

	if (!flag) {
		int pos = k - 1;
		for (int i = 0; i < k; i++) {
			if (ans[i] != 9) pos = i;
		}

		ans[pos]++;
		for (int i = pos + 1; i < k; i++)
			ans[i] = 0;
	}

	for (int i = 0; i < k; i++) {
		for (int j = i; j < n; j += k) {
			ans[j] = ans[i];
		}
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i;
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