#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int a, b;

const int LEN = 1000000000;

int query(int x, int y) {
	if (abs(x) > LEN || abs(y) > LEN) {
		return 0;
	}
	cout << x << " " << y << endl;
	string ans;
	cin >> ans;

	if (ans == "MISS") return 0;
	if (ans == "HIT") return 1;
	if (ans == "CENTER") return 2;
	assert(false);
}

int Find;

pair<int, int> Find_point() {
	for (int x = -LEN + LEN / 4; x <= LEN - LEN / 4; x += LEN / 2) {
		for (int y = -LEN + LEN / 4; y <= LEN - LEN / 4; y += LEN / 2) {
			int have = query(x, y);
			if (have == 0) continue;
			if (have == 2) {
				Find = 1;
			}
			return {x, y};
		}
	}

	for (int x = -LEN / 2; x <= LEN / 2; x += LEN / 2) {
		for (int y = -LEN / 2; y <= LEN / 2; y += LEN / 2) {
			int have = query(x, y);
			if (have == 0) continue;
			if (have == 2) {
				Find = 1;
			}
			return {x, y};
		}
	}
	assert(false);
	return {0, 0};
}

pair<int, int> Find_left(int x, int y) {
	int l = 0, r = LEN * 2 + 229;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int have = query(x - mid, y);
		if (have == 0) {
			r = mid;
		} else {
			l = mid;
			if (have == 2) {
				Find = 1;
				return {x - l, y};
			}
		}
	} 
	return {x - l, y};
}

pair<int, int> Find_right(int x, int y) {
	int l = 0, r = LEN * 2 + 229;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int have = query(x + mid, y);
		if (have == 0) {
			r = mid;
		} else {
			l = mid;
			if (have == 2) {
				Find = 1;
				return {x + l, y};
			}
		}
	} 
	return {x + l, y};
}

pair<int, int> Find_down(int x, int y) {
	int l = 0, r = LEN * 2 + 229;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int have = query(x, y - mid);
		if (have == 0) {
			r = mid;
		} else {
			l = mid;
			if (have == 2) {
				Find = 1;
				return {x, y - l};
			}
		}
	} 
	return {x, y - l};
}

pair<int, int> Find_up(int x, int y) {
	int l = 0, r = LEN * 2 + 229;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int have = query(x, y + mid);
		if (have == 0) {
			r = mid;
		} else {
			l = mid;
			if (have == 2) {
				Find = 1;
				return {x, y + l};
			}
		}
	} 
	return {x, y + l};
}

void solve() {
	Find = 0;
	auto have = Find_point();
	if (Find == 1) return;
	auto Left = Find_left(have.first, have.second);
	if (Find == 1) return;
	auto Right = Find_right(have.first, have.second);
	if (Find == 1) return;
	auto Down = Find_down(Left.first, Left.second);
	if (Find == 1) return;
	auto Up = Find_up(Left.first, Left.second);
	if (Find == 1) return;

	int x = Right.first + Left.first;
	int y = Up.second + Down.second;
	assert(x % 2 == 0 && y % 2 == 0);
	assert(query(x / 2, y / 2) == 2);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t >> a >> b;
	while (t--) {
		solve();
	}
	return 0;
}