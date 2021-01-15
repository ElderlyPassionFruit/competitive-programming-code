#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int INF = 2e18;

int mul(int a, int b) {
	a = min(a, INF);
	b = min(b, INF);
	if (INF / a < b) return INF;
	return a * b;
}

int add(int a, int b) {
	return min(a + b, INF);
}

int a, b, c, d;

map<int, int> have;
set<int> used;

int get(int n) {
	if (n == 0) return 0;
	if (have.count(n)) return have[n];
	have[n] = INF;
	int ans = mul(n, d);
	chkmin(ans, get(n / 2) + (n % 2) * d + a);
	chkmin(ans, get((n + 2) / 2) + (2 - n % 2) * d + a);

	chkmin(ans, get(n / 3) + (n % 3) * d + b);
	chkmin(ans, get((n + 3) / 3) + (3 - n % 3) * d + b);
	
	chkmin(ans, get(n / 5) + (n % 5) * d + c);
	chkmin(ans, get((n + 5) / 5) + (5 - n % 5) * d + c);
	have[n] = ans;
	return ans;
}

void solve() {
	int n;
	have.clear();
	cin >> n >> a >> b >> c >> d;
	cout << get(n) << endl;
	/*cout << "have = " << endl;
	for (auto i : have) {
		cout << i.first << " " << i.second << endl;
	}*/
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}