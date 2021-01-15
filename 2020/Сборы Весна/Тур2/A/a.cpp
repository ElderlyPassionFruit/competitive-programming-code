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
	for (auto &i : a) {
		cin >> i;
	}
}

vector<int> ans;

const int MAXC = 1e6 + 10;
int cnt[MAXC];
int fans[MAXC];

void run() {
	for (int i = 0; i < MAXC; i++) {
		cnt[i] = 0, fans[i] = 0;
	}
	for (auto i : a) {
		cnt[i]++;
	}
	for (int i = 1; i < MAXC; i++) {
		if (!cnt[i]) continue;
		if (i <= k) continue;
		if (i > k) fans[k] += cnt[i];
		for (int j = i + k; j < MAXC; j += i) {
			if (i == j) fans[j]--;
			fans[j] += cnt[i];
		}
	}
	for (auto i : a)
		ans.push_back(fans[i]);
}

void write() {
	for (auto i : ans)
		cout << i << " ";
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