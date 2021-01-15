#pragma GCC optimize("fast-math")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int BUBEN = 30;

ld pows[BUBEN];
int n;
const int MAXN = 3e5 + 10;
pair<int, int> a[MAXN];
set<int> pos;

ld solve(int now) {
	vector<int> r = {now};
	auto it = pos.lower_bound(now);
	while (r.size() < BUBEN && it != pos.end()) {
		r.push_back(*it);
		it++;
	}
	vector<int> l = {now};
	it = pos.lower_bound(now);
	while (l.size() < BUBEN && it != pos.begin()) {
		it--;
		l.push_back(*it);
	}
	ld ans = 0;
	for (int cntL = 0; cntL + 1 < (int)l.size(); cntL++) {
		for (int cntR = 0; cntL + cntR + 1 < BUBEN && cntR  + 1 < (int)r.size(); cntR++) {
			ans += (ld)abs((l[cntL + 1] - l[cntL])) * (r[cntR + 1] - r[cntR]) * pows[cntL + cntR + 1];
		}
	}
	pos.insert(now);
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	pows[0] = 1;
	for (int i = 1; i < BUBEN; i++) {
		pows[i] = pows[i - 1] * 0.5;
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a, a + n);
	reverse(a, a + n);
	pos.insert(-1);
	pos.insert(n);
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		ans += solve(a[i].second) * a[i].first;
	}
	ans /= n;
	ans /= n;
	cout.setf(ios::fixed);
	cout << ans << endl;
	return 0;
}