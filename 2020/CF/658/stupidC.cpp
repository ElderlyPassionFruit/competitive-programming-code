#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, x, y;
vector<int> ans;
vector<int> b;

int calcX(vector<int> have) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += b[i] == have[i];
	}
	return ans;
}

int calcY(vector<int> have) {
	int ans = 0;
	multiset<int> a;
	for (auto i : b) a.insert(i);
	for (auto i : have) {
		if (a.find(i) != a.end()) {
			a.erase(a.find(i));
			ans++;
		}
	}
	return ans;
}

void relax(vector<int> have) {
	if (calcX(have) == x && calcY(have) == y) {
		ans = have;
	}
}

void gen(vector<int> have, int n) {
	if (have.size() == n) {
		relax(have);
		return;
	}
	have.push_back(1);
	while (have.back() <= n + 1) {
		gen(have, n);
		have[have.size() - 1]++;
	}
}

void solve() {
	cin >> n >> x >> y;
	b.resize(n);
	for (auto &i : b) {
		cin >> i;
	}
	ans.clear();
	gen({}, n);
	if (ans.empty()) {
		cout << "NO\n";
	} else {
		cout << "YES\n";
		//return;
		for (auto i : ans) {
			cerr << i << " ";
		}
		cerr << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}