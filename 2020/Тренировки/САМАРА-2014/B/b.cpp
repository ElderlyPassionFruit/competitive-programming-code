#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n;
vector<pair<int, int>> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first;
	for (auto &i : a)
		cin >> i.second;
	sort(all(a));
	int sumA = 0, sumB = 0;
	for (auto i : a) {
		sumA = i.first, sumB += i.second;
		if (sumA <= sumB) {
			cout << "Redemption" << endl;
			return 0;
		}
	}
	cout << "Dire victory" << endl;
	return 0;
}