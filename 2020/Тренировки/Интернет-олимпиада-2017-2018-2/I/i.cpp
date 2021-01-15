#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n, m;
vector<pair<int, int>> a, b;

int stupid_solve() {
	int ans = 0;
	for (auto [vala, posa] : a) {
		for (auto [valb, posb] : b) {
			ans += abs(vala - valb) * (posa - posb);
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	cin >> m;
	b.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> b[i].first;
		b[i].second = i;
	}
	//cout << stupid_solve() << endl;
	sort(all(a));
	sort(all(b));
	int sum_ind, sum_val, sum_add, posB, ans = 0;
	
	/*cout << "A = " << endl;
	for (auto i : a) {
		cout << i.first << " " << i.second << endl;
	}
	cout << "B = " << endl;
	for (auto i : b) {
		cout << i.first << " " << i.second << endl;
	}*/

	sum_ind = 0, sum_val = 0, sum_add = 0;
	posB = 0;
	for (int i = 0; i < n; i++) {
		while (posB < m && b[posB].first <= a[i].first) {
			sum_ind += b[posB].second;
			sum_val += b[posB].first;
			sum_add += b[posB].first * b[posB].second;
			posB++;
		}

		//cout << "sum_ind = " << sum_ind << " sum_val = " << sum_val << " sum_add = " << sum_add << endl;

		ans += a[i].first * (a[i].second * posB - sum_ind);
		ans += sum_add;
		ans -= sum_val * a[i].second;
		//cout << endl;
	}
	//cout << "ans = " << ans << endl;
	swap(n, m);
	swap(a, b);
	sum_ind = 0, sum_val = 0, sum_add = 0;
	posB = 0;
	for (int i = 0; i < n; i++) {
		while (posB < m && b[posB].first <= a[i].first) {
			sum_ind += b[posB].second;
			sum_val += b[posB].first;
			sum_add += b[posB].first * b[posB].second;
			posB++;
		}
		//cout << "sum_ind = " << sum_ind << " sum_val = " << sum_val << " sum_add = " << sum_add << endl;
		ans -= a[i].first * (a[i].second * posB - sum_ind);
		ans -= sum_add;
		ans += sum_val * a[i].second;
	}
	cout << ans << endl;
	return 0;
}