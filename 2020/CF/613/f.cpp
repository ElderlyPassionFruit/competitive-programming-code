#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 100;
int lp[MAXN];
vector<int> p;

void build() {
	for (int i = 2; i < MAXN; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			p.push_back(i);
		}
		for (int j = 0; j < p.size() && i * p[j] < MAXN && p[j] <= lp[i])
			lp[i * p[j]] = p[j];
	}
}

vector<int> stupid_factor(int x) {
	vector<int> ans;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			ans.push_back(i);
			if (i * i != x)
				ans.push_back(x / i);
		}
	}
	return ans;
}

vector<int> smart_fastor(int x) {
	vector<int> ans;
	while (x != 1) {
		ans.push_back(lp[x]);
		x /= lp[x];
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}

int n;

vector<int> have[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		vector<int> x = stupid_factor(a);
		for (auto j : x)
			have[j].push_back(a);
	}
}

vector<int> stupid_have;

ll solve(int Gcd) {
	multiset<int> setik;
	sort(all(have[Gcd]));
	have[Gcd].resize(unique(all(have[Gcd])) - have[Gcd].begin());
	for (int i = 0; i < (int)have[Gcd].size(); i++) {

	}
}

ll ans;

void run() {
	ans = 0;
	for (int i = 1; i < MAXN; i++) {
		chkmax(ans, solve(i) * i);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	read();
	run();
	write();
	return 0;
}