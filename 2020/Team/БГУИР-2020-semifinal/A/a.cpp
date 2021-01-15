#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 21;

ll fact[MAXN];

void build() {
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fact[i] = i * fact[i - 1];
}

int n, a, b;
int p[MAXN];
bool used[MAXN];

int calc_cycles() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		int v = i;
		ans++;
		while (!used[v]) {
			used[v] = true;
			v = p[v] - 1;
		}
	}
	return ans;
}

int cost_cycle(int cnt) {
	return n - cnt;
}

ll get(ll n, ll k) {
	if (n == 0 && k == 0) return 1;
	if (n == 0 || k == 0) return 0;
	return get(n - 1, k - 1) + (n - 1) * get(n - 1, k);
}

ld get_path(int cnt) {
	ld ans = (ld) fact[n] / get(n, cnt);
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cout.setf(ios::fixed);
	build();
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	ld ans = cost_cycle(calc_cycles()) * a;
	//cout << ans << endl;
	for (int i = 1; i <= n; i++) {
		//cout << i << " " << cost_cycle(i) << endl;
		//cout << (ld) get_path(i) * b << endl;
		ans = min(ans, (ld)get_path(i) * b + cost_cycle(i) * a);
	}
	cout << ans << endl;
	return 0;
}