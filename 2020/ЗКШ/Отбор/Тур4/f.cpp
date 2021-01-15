#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

ll n;

void read() {
	cin >> n;
}

ll ans;

int get(ll k, ll n, int cnt) {
	vector<ll> have;
	int sum = 0;
	int p = 0;
	while(n) {
		ll x = n % k;
		//cout << n << " " << k << " " << x << endl;
		n /= k;
		p++;
		if (x == 0) continue;
		if (x > 3) return 0;
		sum += x;
		if (sum > 3) return 0;
		for (int i = 0; i < x; i++)
			have.push_back(p);
	}
	cout << "k = " << k << " cnt = " << cnt << endl;
	for (auto i : have)
		cout << i << " ";
	cout << endl;
	cout << "sum = " << sum << endl;
	if (sum != cnt) return 0;
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	if (cnt == 3) {
		if (have.size() == 3) return 6;
		if (have.size() == 2) return 3;
		return 1;
	}
	else if (cnt == 2) {
		if (have.size() == 2) return 6;
		return 3;
	}
	else {
		return 3;
	}
} 

void run() {
	ans = 0;
	cout << get(2, 4, 2) << endl;
	return;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans += get(i, n, 3);
			if (i * i != n)
				ans += get(n / i, n, 3);
		}
	} 
	ans += get(n, n, 3);
	n--;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans += get(i, n, 2);
			cout << get(i, n, 2) << endl;
			if (i * i != n)
				ans += get(n / i, n, 2);
		}
	}
	ans += get(n, n, 2);
	n--;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans += get(i, n, 1);
			if (i * i != n)
				ans += get(n / i, n, 1);
		}
	} 
	ans += get(n, n, 1);
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