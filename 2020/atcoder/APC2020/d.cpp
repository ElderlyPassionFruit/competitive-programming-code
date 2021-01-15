#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int getMod(string n, int mod) {
	if (mod <= 0) return -1;
	int ans = 0;
	int pow = 1;
	reverse(all(n));
	for (auto i : n) {
		ans += pow * (i - '0') % mod;
		ans %= mod;
		pow *= 2;
		pow %= mod;
	}
	return ans;
}

int binpow(int a, int n, int mod) {
	int ans = 1;
	while (n) {
		if (n & 1) {
			ans = ans * a % mod;
		}
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}

int getCnt(string n) {
	int ans = 0;
	for (auto i : n) {
		ans += i == '1';
	}
	return ans;
}

int n;
string x;

void read() {
	cin >> n >> x;
}

int getAns(int have) {
	int ans = 0;
	while (have) {
		have %= __builtin_popcount(have);
		ans++;
	}
	return ans;
}

vector<int> ans;

void run() {
	int cnt = getCnt(x);
	int valAdd = getMod(x, cnt + 1);
	int valDel = getMod(x, cnt - 1); 
	for (int i = 0; i < n; i++) {
		if (x[i] == '0') {
			if (cnt == 0) {
				ans.push_back(1);
			} else {
				int fans = 1;
				fans += getAns((valAdd + binpow(2, n - 1 - i, cnt + 1)) % (cnt + 1));
				ans.push_back(fans);
			}
		} else if (x[i] == '1') {
			if (cnt == 1) {
				ans.push_back(0);
			} else {
				int fans = 1;
				int val = (valDel - binpow(2, n - 1 - i, cnt - 1));
				val %= cnt - 1;
				val += cnt - 1;
				val %= cnt - 1;
				fans += getAns(val);
				ans.push_back(fans);
			}
		}
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}