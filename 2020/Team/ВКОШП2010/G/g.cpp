#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct child{
	int x, v, ind;
};

bool operator<(const child & a, const child & b) {
	return a.x * b.v > a.v * b.x; 
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(10);
//	freopen("race.in", "r", stdin);
//	freopen("race.out", "w", stdout);
	int n, v;
	cin >> n >> v;
	vector<child> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].v;
		a[i].ind = i + 1;
	}

	sort(all(a));
	ld t = 0;
	vector<pair<int, ld> > ans;
	for (auto i : a) {
		if (i.x <= t * i.v) continue;
		ld myt = i.x - i.v * t;
		myt /= (i.v + v);

		ans.push_back({i.ind, myt * v});
		t += 2 * myt;
	}
	cout << t << endl;
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i.first << " " << i.second << "\n";
	}
	return 0;
}