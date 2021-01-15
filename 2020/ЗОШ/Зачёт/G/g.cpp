#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int ask (int k) {
	cout << "? " << k << endl;
	int ans;
	cin >> ans;
	return k * (k + 1) / 2 - ans;
}


signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

	int n;
	cin >> n;

	int sum = ask(n);

	int l = 1, r = n + 1;
	int first = -1;
	bool f = false;
	while (r - l != 1) {
		int m = (r + l) / 2;
		int ans = ask(m - 1);
		if (ans == 0 || ans == sum) {
			if (ans == 0)
				l = m;
			else
				r = m;
			continue;
		}
		if (first != -1) {
			if (f)
				ans -= first;
			if (ans == 0 || ans == sum - first) {
				if (ans == 0)
					l = m;
				else
					r = m;
				continue;
			}
			set<int> sss = {first,ans, sum-first-ans};
			if(sss.size()<3)
			{
				while(1);
			}
			cout << "! " << first << ' ' << sum - first - ans << ' ' << ans << endl;
			return 0;
		}
	//	cerr << ans << ' ' << m << ' ' << l << ' ' << r << '\n';
		int ans1 = sum - ans;
		if (ans1 >= m * 2 + 1) {
			first = ans;
			l = m;
			f = true;
		} else {
			first = ans1;
			r = m;
		}
	}
	assert(0);
	return 0;
}