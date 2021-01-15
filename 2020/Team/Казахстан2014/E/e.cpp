#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m, k;
vector<int> a[4];

multiset<int> have;
int sum;
int cnt;

void relax() {
	while (have.size() > cnt) {
		sum -= *(--have.end());
		have.erase(--have.end());
	}
}

void add(int x) {
	have.insert(x);
	sum += x;
	relax();
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		int t;
		int f1, f2;
		cin >> t >> f1 >> f2;
		a[f1 * 2 + f2].push_back(t);
	}
	for (int i = 0; i < 4; i++) {
		sort(all(a[i]));
	}
	if (a[3].size() + min(a[1].size(), a[2].size()) < k) {
		cout << -1 << endl;
		exit(0);
	}
	sum = 0;
	cnt = m;
	for (int i = 0; i < (int)a[0].size(); i++) {
		add(a[0][i]);
	}
	int ans = 2e9 + 228 + 1337;
	for (auto i : a[1]) sum += i;
	for (auto i : a[2]) sum += i;
	for (int i = 0; i <= min((int)a[3].size(), k); i++) {
		while (a[1].size() > k - i) {
			add(a[1].back());
			sum -= a[1].back();
			a[1].pop_back();
		}
		while (a[2].size() > k - i) {
			add(a[2].back());
			sum -= a[2].back();
			a[2].pop_back();
		}
		cnt = k - i;
		relax();
		if (min(a[1].size(), a[2].size()) + i >= k) {
			ans = min(ans, sum);
		} 
		if (i == a[3].size()) break;
		sum += a[3][i];
	}
	cout << ans << endl;
	return 0;
}