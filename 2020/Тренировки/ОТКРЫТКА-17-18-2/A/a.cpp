#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, q;
vector<int> a;

void read() {
	cin >> n >> q;
}

ll solve() {
	int pos;
	cin >> pos;
	while (pos % 2 == 0) {
		int cnt = pos / 2;
		pos += n - cnt;
	}
	return (pos + 1) / 2;
}

vector<ll> ans;

void run() {
	while (q--)
		ans.push_back(solve());
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