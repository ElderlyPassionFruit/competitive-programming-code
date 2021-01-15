#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

void no() {
	cout << "NO\n";
	exit(0);
}

vector<pair<int, int> > ans;

bool check() {
	for (int i = 1; i < n; i++) {
		if (a[i] > a[i - 1]) return false;
	}
	return true;
}

void stupid_solve() {
	if (n == 4) {
		if (a[0] < a[3]) {
			swap(a[0], a[3]);
			ans.push_back({0, 3});
		} 
	}
	if (n == 5) {
		while (true) {
			if (a[0] < a[1]) {
				ans.push_back({1, 4});
				ans.push_back({0, 4});
				ans.push_back({1, 4});
				swap(a[0], a[1]);
				continue;
			}
			if (a[0] < a[3]) {
				ans.push_back({0, 3});
				swap(a[0], a[3]);
				continue;
			}
			if (a[0] < a[4]) {
				ans.push_back({0, 4});
				swap(a[0], a[4]);
				continue;
			}
			if (a[1] < a[3]) {
				ans.push_back({0, 3});
				ans.push_back({1, 4});
				ans.push_back({0, 4});
				ans.push_back({0, 3});
				ans.push_back({1, 4});
				swap(a[1], a[3]);
				continue;
			}
			if (a[1] < a[4]) {
				ans.push_back({1, 4});
				swap(a[1], a[4]);
				continue;
			}
			if (a[3] < a[4]) {
				ans.push_back({0, 3});
				ans.push_back({0, 4});
				ans.push_back({0, 3});
				swap(a[3], a[4]);
				continue;
			}
			break;
		}
	}
	if (!check()) no();
}

void change(int pos) {
	if (a[pos] >= a[pos + 1]) return;
	if (pos + 4 < n) {
		ans.push_back({pos, pos + 4});
		ans.push_back({pos + 1, pos + 4});
		ans.push_back({pos, pos + 4});
		swap(a[pos], a[pos + 1]);
	}
	else if (pos + 3 < n) {
		ans.push_back({pos, pos + 3});
		ans.push_back({pos - 1, pos + 3});
		ans.push_back({pos - 1, pos + 2});
		ans.push_back({pos - 2, pos + 2});

		ans.push_back({pos - 2, pos + 1});

		ans.push_back({pos - 2, pos + 2});
		ans.push_back({pos - 1, pos + 2});
		ans.push_back({pos - 1, pos + 3});
		ans.push_back({pos, pos + 3});
		swap(a[pos], a[pos + 1]);
	}
	else {
		ans.push_back({pos, pos - 3});
		ans.push_back({pos - 3, pos + 1});
		ans.push_back({pos, pos - 3});
		swap(a[pos], a[pos + 1]);
	}
}

void smart_solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j + 1 < n; j++) {
			change(j);
		}
	}
	assert(check());
}

void run() {
	if (n <= 5) {
		stupid_solve();
	}
	else {
		smart_solve();
	}
}

void write() {
	cout << "YES\n";
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i.first + 1 << " " << i.second + 1 << "\n";
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