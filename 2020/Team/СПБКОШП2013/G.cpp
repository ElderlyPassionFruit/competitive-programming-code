#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int long long
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
	auto x = a;
	for (int i = 0; i < k && x[i] < 0; i++)
		x[i] *= -1;
	int fans = 0; 
	for (auto i : x)
		fans += i;
	x = a;
	reverse(x.begin(), x.end());
	for (int i = 0; i < k && x[i] > 0; i++)
		x[i] *= -1;
	int fans2 = 0;
	for (auto i : x)
		fans2 += i;
	cout << max(abs(fans), abs(fans2)) << endl;
	return 0;
}