#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;

void read() {
	cin >> n;
}

const int MAXN = 2e5 + 10;
int lp[MAXN];
vector<int> pr;

void build() {
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && pr[j] * i <= n; j++) {
			lp[pr[j] * i] = pr[j];
		}
	}
}

vector<int> get(int x) {
	vector<pair<int, int>> p;
	while (lp[x]) {
		if (p.empty() || p.back().first != lp[x]) {
			p.push_back({lp[x], 0});
		}
		p[p.size() - 1].second++;
		x /= lp[x];
	}
	vector<int> ans;
	for (auto i : p) {
		if (i.second % 2 == 1) {
			ans.push_back(i.first);
		}
	}
	sort(all(ans));
	return ans;
}

ll ans;

void run() {
	build();
	map<vector<int>, int> have;
	for (int i = 1; i <= n; i++) {
		have[get(i)]++;
	}
	for (auto [mask, cnt] : have) {
		ans += (ll)cnt * (cnt - 1) * (cnt - 2) / 6;
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