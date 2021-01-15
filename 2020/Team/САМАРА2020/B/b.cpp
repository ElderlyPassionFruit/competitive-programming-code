#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll	
int n, t;
vector<int> a, b;


signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> t;
	vector<int> x(n);
	for (auto &i : x)
		cin >> i;
	sort(all(x));
	for (auto i : x) {
		if (i < 0)
			a.push_back(i);
		else
			b.push_back(i);
	}
	for (auto &i : a)
		i *= -1;
	sort(all(a));
	sort(all(b));
	int ans = 0;
	for (int i = 0; i <= (int)a.size(); i++) {
		if (i > 0 && a[i - 1] > t) break;
		chkmax(ans, i);
		int nt = 0;
		if (i > 0) nt += 2 * a[i - 1];
		if (nt > t) continue;
		chkmax(ans, i + (int)(upper_bound(all(b), t - nt) - b.begin()));
	}
	swap(a, b);
	
	for (int i = 0; i <= (int)a.size(); i++) {
		if (i > 0 && a[i - 1] > t) break;
		chkmax(ans, i);
		int nt = 0;
		if (i > 0) nt += 2 * a[i - 1];
		if (nt > t) continue;

		chkmax(ans, i + (int)(upper_bound(all(b), t - nt) - b.begin()));
	}

	cout << ans << endl;
	return 0;
}