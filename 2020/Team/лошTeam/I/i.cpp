#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
string s;

void read() {
	cin >> s;
	n = s.size();
}

vector<int> have;

void build() {
	vector<int> pos;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)pos.size(); j++) {
			if (s[i] == s[pos[j]]) {
				pos.erase(pos.begin() + j);
				break;
			}
		}
		pos.push_back(i);
		int mask = 0;
		for (int j = (int)pos.size() - 1; j >= 0; j--) {
			mask |= (1 << (s[pos[j]] - 'a'));
			if (i != n - 1 && ((mask >> (s[i + 1] - 'a')) & 1)) break;
			have.push_back(mask);
		}
	}
	sort(all(have));
}

int get(int mask) {
	return upper_bound(all(have), mask) - lower_bound(all(have), mask);
}

void solve() {
	string s;
	cin >> s;
	int mask = 0;
	for (auto i : s) {
		mask |= (1 << (i - 'a'));
	}
	cout << get(mask) << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	read();
	build();
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
	return 0;
}