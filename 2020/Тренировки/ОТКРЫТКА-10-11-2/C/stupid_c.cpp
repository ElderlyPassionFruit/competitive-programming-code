#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;
vector<int> a;
mt19937 rnd(time(0));
void read() {
	/*n = 20;
	a.resize(n);
	for (auto &i : a) {
		i = rnd() % 100 + 1;
	}
	sort(all(a));
	reverse(all(a));
	cout << "a = " << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;*/
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	reverse(all(a));
}

vector<int> pref;

void build() {
	pref = a;
	for (int i = 1; i < n; i++)
		pref[i] += pref[i - 1];
}

int get(int l, int r) {
	return pref[r] - (l > 0 ? pref[l - 1] : 0);
}

int calc(int p, int q) {
	if (p > q) return 1e18;
	int ans1 = 0, ans2 = 0;
	ans1 += get(0, p - 1);
	int it = 0;
	for (int i = p; i < n; i += q) {
		if (it % 2) {
			ans1 += get(i, min(n, i + q) - 1);
		}
		else {
			ans2 += get(i, min(n, i + q) - 1);
		}
		it++;
	}
	return abs(ans1 - ans2);
}

int ans = 1e18;
pair<int, int> fans;
void run() {
	build();
	for (int q = 1; q <= n; q++) {
		for (int p = 1; p <= n; p++) {
			int kek = calc(p, q);
			if (kek < ans) {
				ans = kek;
				fans = {p, q};
			}
			//cout << calc(p, q) << " ";
		}
		//cout << endl;
	}
}

void write() {
	cout << ans << endl;
	return;
	cout << fans.first << " " << fans.second << endl;
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