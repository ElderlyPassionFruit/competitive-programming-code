#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<int> nxt(vector<int> a) {
	int n = a.size();
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = min(a[(i - 1 + n) % n], a[(i + 1) % n]);
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	for (int i = 0; i < k; i++)
		a = nxt(a);
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	return 0;
}