#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
set<pair<int, int>> a;
multiset <int> t;
vector<vector<int> > ans;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.insert({x, i + 1});
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		t.insert(x);
	}
}

void no() {
	cout << "NO" << "\n";
	exit(0);
}

void run() {
	while (t.size()) {
		
		if (t.size() == 1) {
			int x = *t.begin();
			int y = (*a.begin()).first;
			if (x != y) {
				no();
			}
			break;
		}

		int lt = *t.begin();
		t.erase(t.begin());
		
		auto pos = a.upper_bound({lt, (int)1e9});
		if (pos == a.begin())
			no();
		
		pos--;
		auto la = *pos;
		a.erase(pos);

		auto x = a.lower_bound({lt, -1});
		if (x == a.end())
			no();
		
		a.erase(x);
		auto ra = *x;
		
		int d = min(lt - la.first, ra.first - lt);
		la.first += d;
		ra.first -= d;

		ans.push_back({la.second, ra.second, d});

		if (la.first == lt && ra.first == lt)
			a.insert(la);
		else if (la.first != lt)
			a.insert(la);
		else
			a.insert(ra);
	}
}

void write() {
	cout << "YES" << "\n";
	cout << ans.size() << "\n";
	for (auto i : ans) {
		for (auto j : i)
			cout << j << " ";
		cout << "\n"; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}