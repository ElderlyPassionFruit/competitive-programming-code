#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int long long
struct event{
	int sum, ind;
	event() {}
	event(int a, int b) {
		sum = a, ind = b;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.sum, a.ind) < tie(b.sum, b.ind);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	set<event> s;
	int sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		sum += a[i];
		s.insert(event(sum, i));
	}
	pair <int, pair <int, int> > ans;
	ans.first = 1e18 + 10;
	int mysum = 0;
	for (int i = 0; i < n - 1; i++) {
		mysum += a[i];
		s.erase(event(sum, i));
		sum -= a[i];
		auto it1 = s.lower_bound(event(mysum, 0));
		if (it1 != s.end()) {
			ans = min(ans, make_pair(abs(it1->sum - mysum), make_pair(i, it1->ind)));
		}
		if (it1 != s.begin()) {
			--it1;
			ans = min(ans, make_pair(abs(it1->sum - mysum), make_pair(i, it1->ind)));
		}
	}
	cout << ans.first << " " << ans.second.first + 1 << " " << ans.second.second + 1 << endl;
	return 0;
}