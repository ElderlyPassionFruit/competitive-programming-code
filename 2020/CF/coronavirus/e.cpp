#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 2e6 + 10;
int n;
int a[MAXN];
int x;

void read() {
	cin >> n;
	for (int i = 0; i < (n + 1) / 2; i++)
		cin >> a[i];
	cin >> x;
}

int ans;
int mx_len;
void relax(int sum, int len) {
	if (sum <= 0) {
		mx_len = -1;
		return;
	}
	if (x == 0) {
		return;
	}
	int cnt = (sum - 1) / abs(x);
	chkmin(mx_len, len + cnt);
}

void run() {
	if (x > 0) {
		int sum = 0;
		for (int i = 0; i < (n + 1) / 2; i++) {
			sum += a[i];
		}
		sum += x * (n / 2);
		if (sum <= 0) {
			ans = -1;
		} else {
			ans = n;
		}
		return;
	}
	for (int i = (n + 1) / 2 - 2; i >= 0; i--) {
		a[i] += a[i + 1];
	}
	mx_len = n;
	ans = -1;
	for (int i = 0; i < (n + 1) / 2; i++) {
		relax(a[i], (n + 1) / 2 - i);
		if (mx_len == n - i) {
			ans = mx_len;
			return;
		}
	}	
}

void write() {
	cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}