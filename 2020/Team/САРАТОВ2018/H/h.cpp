#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
struct event{
	int time, ind;
	event() {}
	event(int a, int b) {
		time = a, ind = b;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.time, a.ind) < tie(b.time, b.ind);
}

struct help{
	int x, y;
	help() {}
	help(int a, int b) {
		x = a, y = b;
	}
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;

	vector<help> h(m);
	for (auto &i : h)
		cin >> i.x >> i.y;

	set<event> t;
	for (int i = 0; i < m; i++)
		t.insert({0, i});
	int T = 0;
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		auto ev = *t.begin();
		t.erase(t.begin());
		ans[i] = ev.ind;
		ev.time += a[i] * h[ev.ind].y + h[ev.ind].x;
		t.insert(ev);
		T = max(T, ev.time); 
	}
	cout << T << endl;
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << endl;
	return 0;
}