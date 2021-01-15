#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXMEM = 10000;

map<int, vector<string>> have;

vector<int> get(int a) {
	return {a};
}

vector<int> get(int a, int b) {
	return {a + b, a - b, a * b, b - a};
}

vector<int> get(int a, int b, int c) {
	return {
		a + b + c,
		a + b - c,
		a - b + c,
		(-a) + b + c,
		a - b - c,
		(-a) + b - c,
		(-a) - b + c,
		(-a) - b - c,
		a * b + c,
		a + b * c,
		a * b * c,
		(-a) * b + c,
		a + (-b) * c,
		(-a) * b * c
	};
}

vector<int> get(int a, int b, int c, int d) {
	vector<int> fans = get(a, b, c);
	vector<int> ans;
	for (auto i : fans) {
		auto have = get(i, d);
		for (auto j : have) {
			ans.push_back(j);
		}
	}
	return ans;
}

void gen() {
	for (int i = 0; i < MAXMEM; i++) {
		string s = to_string(i);
		reverse(all(s));
		while (s.size() < 4) s += "0";
		reverse(all(s));
		vector<int> ans, now;
		now = get(i);
		for (auto x : now) ans.push_back(x);
		now = get(i / 1000, i % 1000);
		for (auto x : now) ans.push_back(x);
		now = get(i / 100, i % 100);
		for (auto x : now) ans.push_back(x);
		now = get(i / 10, i % 10);
		for (auto x : now) ans.push_back(x);
		now = get(i / 1000, (i % 1000) / 100, i % 100);		
		for (auto x : now) ans.push_back(x);
		sort(all(ans));
		ans.resize(unique(all(ans)) - ans.begin());
		for (auto x : ans) {
			have[x].push_back(s);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	gen();
	int k, m;
	cin >> k >> m;
	set<string> ans;
	for (int i = -MAXMEM; i < MAXMEM; i++) {
		if ((int)ans.size() == m) break; 
		for (auto L : have[i]) {
			if ((int)ans.size() == m) break;
			for (auto R : have[k - i]) {
				if ((int)ans.size() == m) break;
				ans.insert(L + R);
			}
		}
	}
	assert(ans.size() == m);
	for (auto i : ans) {
		cout << i << "\n";
	}
	return 0;
}