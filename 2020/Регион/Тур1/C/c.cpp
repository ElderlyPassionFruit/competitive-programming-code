#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int n, m, k;

void read() {
	cin >> n >> m >> k;
}

vector<pair<int, int> > fact(int n) {
	vector<pair<int, int> > ans;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans.push_back({i, 0});
			while (n % i == 0) {
				ans[ans.size() - 1].second++;
				n /= i;
			}
		}
	}
	if (n > 1) ans.push_back({n, 1}); 
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}

const int MAXMUL = 65;

int dp[MAXMUL][2];
int cnt[MAXMUL][MAXMUL];

vector<int> mask[MAXMUL];
vector<int> d;
vector<int> cnt_d;
int have;

vector<vector<int> > gen(vector<vector<int> > have) {
	if (!have.empty() && have[0].size() == d.size()) return have;
	vector<vector<int> > ans;
	int sz = 0;
	if (!have.empty())
		sz = have[0].size();
	for (int i = 0; i <= cnt_d[sz]; i++) {
		for (auto &j : have)
			j.push_back(i);
		auto fans = gen(have);
		for (auto j : fans)
			ans.push_back(j);
		for (auto &j : have)
			j.pop_back();
	}
	return ans;
}

int get_num(int all, int diff) {
	int old = all / diff;
	int ans = 0;
	for (int i = 1; i <= k; i++) {
		bool flag = all == __gcd(old * i, m);
		flag &= i % diff == 0;
		if (flag)
			ans++;
	}
	return ans;
}

int pows(int x, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= x;
	return ans;
}

int get(vector<int> have_d) {
	int ans = 1;
	for (int i = 0; i < have_d.size(); i++)
		ans *= pows(d[i], have_d[i]);
	return ans;
}

void build() {
	auto a = fact(m);
	for (auto i : a)
		d.push_back(i.first), cnt_d.push_back(i.second);
	while (d.size() < 5)
		d.push_back(1), cnt_d.push_back(0);

	auto b = gen({{}});
	sort(all(b), [&] (vector<int> i, vector<int> j) {return get(i) < get(j);});
	b.pop_back();
	have = b.size();
	for (int i = 0; i < have; i++)
		mask[i] = b[i];

	for (int i = 0; i < have; i++) {
		for (int j = i; j < have; j++) {
			int x = get(mask[j]);
			int y = get(mask[i]);
			if (x % y != 0) continue;
			cnt[i][j] = get_num(x, x / y);
		}
	}
}

void recalc() {
	for (int i = 0; i < have; i++) {
		dp[i][0] = dp[i][1];
		dp[i][1] = 0;
	}
}

void calc() {
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int a = 0; a < have; a++) {
			for (int b = a; b < have; b++) {
				int & now = dp[a][0];
				int & nxt = dp[b][1];
				nxt = add(nxt, mul(now, cnt[a][b]));
			}
		}
		recalc();
	}
}

int ans = 0;

void make_ans() {
	ans = 1;
	for (int i = 0; i < n; i++)
		ans = mul(ans, k);
	for (int i = 0; i < have; i++)
		ans = sub(ans, dp[i][0]);
}

void run() {
	build();
	calc();
	make_ans();
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