#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> d;
int a, b;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	d.resize(n);
	for (auto &i : d) {
		cin >> i;
	}
	sort(all(d));
	d.resize(unique(all(d)) - d.begin());
	cin >> b >> a;
	int ans = 0;
	while (a != b) {
		vector<int> nd;
		int nxt = b - 1;
		for (auto i : d) {
			if (b - b % i < a) continue;
			nd.push_back(i);
			nxt = min(nxt, b - b % i);
		}
		b = nxt;
		d = nd;
		ans++;
	}
	cout << ans << endl;
	return 0;
}