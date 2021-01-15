#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

const int INF = 2e9 + 228 + 1337;

int mul(int a, int b) {
	a = min(a, INF);
	b = min(b, INF);
	return min(INF, a * b);
}

int gcd(int a, int b) {
	if (!a) return b;
	if (!b) return a;
	while (b) {
		a %= b;
		swap(a, b); 	
	}
	return a;
}

int lcm(int a, int b) {
	if (!a) return b;
	if (!b) return a;
	int g = gcd(a, b);
	return mul(a / g, b);
}

int n, m;
vector<int> a;
vector<int> pref, suff;

void build(vector<int> & pref, vector<int> & a) {
	pref.resize(n);
	pref = a;
	for (int i = 1; i < n; i++) {
		pref[i] = lcm(pref[i - 1], a[i]);
	}
}

void build() {
	build(pref, a);
	reverse(all(a));
	build(suff, a);
	reverse(all(suff));
	reverse(all(a));
}

void Never() {
	cout << "Never" << "\n";
}

void solve(int pos) {
	if (pos > 0 && pref[pos - 1] == INF) {
		Never();
		return;
	}
	if (pos + 1 < n && suff[pos + 1] == INF) {
		Never();
		return;
	}
	int ans = 0;
	if (pos > 0) ans = lcm(ans, pref[pos - 1]);
	if (pos + 1 < n) ans = lcm(ans, suff[pos + 1]);
	if (ans == INF) {
		Never();
		return;
	}
	if (ans % a[pos] == 0) {
		Never();
		return;
	}
	int add = ans;
	ans = mul((m + ans - 1) / ans, ans);
	if (ans == INF) {
		Never();
	}
	while (ans % a[pos] == 0) {
		ans += add;
	}
	ans -= m;
	assert(ans >= 0);
	if (ans > 1000000000) {
		Never();
		return;
	}
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	build();
	/*cout << "pref = " << endl;
	for (auto i : pref)
		cout << i << " ";
	cout << endl;
	for (auto i : suff) {
		cout << i << " ";
	}
	cout << endl;*/
	for (int i = 0; i < n; i++) {
		solve(i);
	}
	return 0;
}