#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(k);
	for (auto &i : a)
		cin >> i;
}

int calc(int mask) {
	vector<int> have;
	for (int i = 0; i < k; i++) {
		if ((mask >> i) & 1) {
			have.push_back(a[i]);
		}
	}
	int place = 0;
	for (int i = 1; i < have.size(); i++) {
		if (have[i] == have[i - 1] + 1) return k;
			place += (have[i] - have[i - 1] - 2) / 2;
	}
	if (!have.empty()) {
		place += (have[0] - 1) / 2;
		place += (n - have.back()) / 2;
	}
	else {
		place = n;
	}
	if (place + have.size() >= k) {
		return k - have.size();
	}
	return k;
}

int ans;

void run() {
	sort(all(a));
	ans = k;
	//calc(15);
	//return;
	for (int i = 0; i < (1 << k); i++) {
		//cout << i << " " << calc(i) << endl;
		ans = min(ans, calc(i));
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