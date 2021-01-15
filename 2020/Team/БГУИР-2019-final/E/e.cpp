#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

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

const int MAXN = 1e5 + 10;
int suff[MAXN];

int get(int x) {
	int ans = 0;
	while (x) {
		ans += x % 10;
		x /= 10;
	}
	return ans;
}

int brute(string a) {
	int n = 0;
	for (auto i : a) {
		n = n * 10 + i - '0';
	}
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		ans += abs(get(i) - get(i - 1));
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string n;
	cin >> n;
	//cout << brute(n) << endl;
	int N = 0;
	for (auto i : n) {
		N = add(mul(N, 10), i - '0');
	}
	N = sub(N, 1);
	/*reverse(all(n));

	n += '0';
	for (int i = 0; i < n.size(); i++) {
		if (n[i] != '9') {
			n[i]++;
			break;
		} else {
			n[i] = '0';
		}
	}
	if (n.back() == '0') n.pop_back();
	reverse(all(n));*/
	int ans = 0;
	suff[0] = 0;
	for (int i = 1; i <= n.size(); i++) {
		suff[i] = add(mul(suff[i - 1], 10), n[i - 1] - '0');
		//cout << suff[i] << " "; 
	}
	//cout << endl;
	int now = 8;
	for (int i = n.size(); i >= 2; i--) {
		ans = add(ans, mul(now, sub(suff[i - 1], suff[i - 2])));
		now += 9;
	}
	//cout << "ans = " << ans << endl;
	ans = add(ans, sub(N, suff[n.size() - 1]));
	cout << ans << endl;
	return 0;
}




