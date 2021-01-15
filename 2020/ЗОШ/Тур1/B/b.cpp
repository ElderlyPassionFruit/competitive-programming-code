#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int b, n, e;
int sb, sn, se;
vector<int> a;

void read() {
	cin >> b >> n >> e;
	cin >> sb >> sn >> se;
	a.resize((b + n + e) / 2);
	for (auto &i : a)
		cin >> i;
}

bool check(int x) {
	vector<int> fa;
	for (auto i : a) {
		fa.push_back((i + x - 1) / i);
	}
	/*cout << "fa = " << endl;
	for (auto i : fa)
		cout << i << " ";
	cout << endl;*/
	sort(all(fa));
	int fb = b, fn = n, fe = e;
	for (auto i : fa) {
		if (fb >= 2 && i <= sb * 2) {
			fb -= 2;
			continue;
		}
		if (fb && fn && i <= sb + sn) {
			fb--;
			fn--;
			continue;
		}
		if (sb + se <= sn * 2) {
			if (fb && fe && i <= sb + se) {
				fb--;
				fe--;
				continue;
			}
			if (fn >= 2 && i <= sn * 2) {
				fn -= 2;
				continue;
			}
		}
		else {
			if (fn >= 2 && i <= sn * 2) {
				fn -= 2;
				continue;
			}
			if (fb && fe && i <= sb + se) {
				fb--;
				fe--;
				continue;
			}
		}
		if (fn && fe && i <= sn + se) {
			fn--;
			fe--;
			continue;
		}
		if (fe >= 2 && i <= se * 2) {
			fe -= 2;
			continue;
		}
		return false;
	}
	return true;
}

ll ans;

void run() {
	int l = 0, r = 1e9;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
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