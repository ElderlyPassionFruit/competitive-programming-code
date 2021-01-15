#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXBIT = 31;
int cnt_bit[MAXBIT];

ll get_ans() {
	ll ans = 0;
	for (int i = 0; i < MAXBIT; i++) {
		ans += (1LL << i) * (ll) cnt_bit[i];
	}
	return ans;
}

const int MAXN = 2e5 + 10;

int n, q, cnt_out = 0;
int pref[MAXN], now = 0;
int a[MAXN];

void add(int ind) {
	for (int i = 0; i < MAXBIT; i++) {
		if ((a[ind] >> i) & 1)
			cnt_bit[i]++;
	}
	pref[ind] = now;
}

void del(int ind) {
	a[ind] ^= (now ^ pref[ind]);
	for (int i = 0; i < MAXBIT; i++) {
		if ((a[ind] >> i) & 1)
			cnt_bit[i]--;
	}
	cnt_out++;
}

void make(int x) {
	for (int i = 0; i < MAXBIT; i++) {
		if ((x >> i) & 1)
			cnt_bit[i] = (n - cnt_out) - cnt_bit[i];
	}
	now ^= x;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		add(i);
	}
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			cin >> a[n];
			add(n);
			n++;
		}
		else if (t == 2) {
			int p;
			cin >> p;
			p--;
			del(p);
		}
		else if (t == 3) {
			int e;
			cin >> e;
			make(e);
		}
		cout << get_ans() << "\n";
	}
	return 0;
}



