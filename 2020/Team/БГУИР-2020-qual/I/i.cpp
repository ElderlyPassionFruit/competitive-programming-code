#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct num{
	int val, ind;
	num() {}
	num(int _val, int _ind) {
		val = _val, ind = _ind;
	}
};

bool operator<(const num & a, const num & b) {
	return a.val < b.val;
}

int n;
vector<int> cnt;
vector<num> a;

void read() {
	string s;
	cin >> s;
	cnt.assign(10, 0);
	for (auto i : s) cnt[i - '0']++;
}

void solve() {
	read();	
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}