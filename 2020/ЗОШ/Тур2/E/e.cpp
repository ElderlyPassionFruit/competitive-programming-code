#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
const int INF = 1e9;
unordered_map<int, vector<int>> good_num;
int lp[MAXN];
vector<int> pr;

vector<int> factorization(int n) {
	vector<int> ans;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			ans.push_back(i);
			if (i != n / i)
			ans.push_back(n / i);
		}
	}
	return ans;
}

void build() {
	for (int i = 2; i < MAXN; i++) {
		if (!lp[i]) {
			pr.push_back(i);
			lp[i] = i;
		}
		for (int j = 0; j < (int) pr.size() && pr[j] * i < MAXN && pr[j] <= lp[i]; j++)
			lp[i * pr[j]] = pr[j];
	}

	for (auto i : pr) {
		ll ans = i + 1;
		ll x = i;
		while (ans < INF) {
			good_num[ans].push_back(x);
			x *= i;
			ans += x;
		}
	}
}

bool check_prime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}

vector<int> d;
int SQ;

void make_sq(int n) {
	SQ = max((int)sqrt(n) - 5, 0);
	while (SQ * SQ <= n)
		SQ++;
}

void make_d(int n) {
	d = factorization(n);
	vector<int> ans;
	for (auto i : d)
		if (check_prime(i - 1) || good_num.count(i))
			ans.push_back(i);
	d = ans;
	sort(all(d));
	reverse(all(d));
}

vector<int> solve(int n, int pos) {
	if (n == 1) return {1};
	vector<int> ans;
	for (int j = pos; j < d.size(); j++) {
		int i = d[j];
		if (n % i) continue;
		if (!good_num.count(i)) {
			bool flag = check_prime(i - 1);
			if (!flag) continue; 
			auto fans = solve(n / i, j);
			for (auto x : fans)
				if (__gcd(i - 1, x) == 1)
					ans.push_back((i - 1) * x);
		}
		else { 
			auto fans = solve(n / i, j	);
			for (auto x : fans)
				for (auto y : good_num[i])
					if (__gcd(x, y) == 1)
						ans.push_back(x * y);
		}
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}

vector<int> smart(int n) {
	make_sq(n);
	make_d(n);
	auto ans = solve(n, 0);
	sort(all(ans));
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> ans = smart(n);
		if (ans.empty())
			cout << -1 << "\n";
		else {
			for (auto i : ans)
				cout << i << " ";
			cout << endl;
		}
	}
	return 0;
}
