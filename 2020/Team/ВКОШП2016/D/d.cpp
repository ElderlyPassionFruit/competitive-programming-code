#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<vector<char> > table;
vector<vector<int> > up[26];

void build_up() {
	for (int i = 0; i < 26; i++) {
		up[i].resize(n, vector<int> (m, -1));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 26; k++) {
				if (i > 0)
					up[k][i][j] = up[k][i - 1][j];	
			}
			up[table[i][j] - 'a'][i][j] = i;	
		}
	}
}

void build_down() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 26; k++) {
				up[k][i][j] = -1;
				if (i < n - 1)
					up[k][i][j] = up[k][i + 1][j];	
			}
			up[table[i][j] - 'a'][i][j] = i;	
		}
	}
}

void build_Left() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 26; k++) {
				up[k][i][j] = -1;
				if (j > 0)
					up[k][i][j] = up[k][i][j - 1];	
			}
			up[table[i][j] - 'a'][i][j] = j;	
		}
	}
}

void build_Right() {
	for (int i = 0; i < n; i++) {
		for (int j = m - 1; j >= 0; j--) {
			for (int k = 0; k < 26; k++) {
				up[k][i][j] = -1;
				if (j < m - 1)
					up[k][i][j] = up[k][i][j + 1];	
			}
			up[table[i][j] - 'a'][i][j] = j;	
		}
	}
}

ll get(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

const int INF = 1e9;

pair<int, int> get_up(int x, int y, char a) {
	int ans = -INF;
	for (int i = 0; i < 26; i++) {
		if (a - 'a' == i) continue;
		if (up[i][x][y] != -1) {
			ans = max(ans, up[i][x][y]);
		}
	}
	return {ans, y};
}

pair<int, int> get_down(int x, int y, char a) {
	int ans = INF;
	for (int i = 0; i < 26; i++) {
		if (a - 'a' == i) continue;
		if (up[i][x][y] != -1) {
			ans = min(ans, up[i][x][y]);
		}
	}
	return {ans, y};

}

pair<int, int> get_Left(int x, int y, char a) {
	int ans = -INF;
	for (int i = 0; i < 26; i++) {
		if (a - 'a' == i) continue;
		if (up[i][x][y] != -1) {
			ans = max(ans, up[i][x][y]);
		}
	}
	return {x, ans};
}

pair<int, int> get_Right(int x, int y, char a) {
	int ans = INF;
	for (int i = 0; i < 26; i++) {
		if (a - 'a' == i) continue;
		if (up[i][x][y] != -1) {
			ans = min(ans, up[i][x][y]);
		}
	}
	return {x, ans};
}

void solve_Left(int x, int y, pair<ll, pair<pair<int, int> , pair<int, int>>> & ans) {
	if (x + 1 < n) {
		pair<int, int> a = {x + 1, y};
		if (y - 1 >= 0) {
			pair<int, int> b = get_Left(x, y - 1, table[x + 1][y]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));
		}
	}
	if (x - 1 >= 0) {
		pair<int, int> a = {x - 1, y};
		if (y - 1 >= 0) {
			pair<int, int> b = get_Left(x, y - 1, table[x - 1][y]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));
		}
	}
}

void solve_Right(int x, int y, pair<ll, pair<pair<int, int> , pair<int, int>>> & ans) {
	if (x + 1 < n) {
		pair<int, int> a = {x + 1, y};
		if (y + 1 < m) {
			pair<int, int> b = get_Right(x, y + 1, table[x + 1][y]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));	
		}
	}
	if (x - 1 >= 0) {
		pair<int, int> a = {x - 1, y};
		if (y + 1 < m) {
			pair<int, int> b = get_Right(x, y + 1, table[x - 1][y]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));	
		}
	}
}

void solve_down(int x, int y, pair<ll, pair<pair<int, int> , pair<int, int>>> & ans) {
	if (y + 1 < m) {
		pair<int, int> a = {x, y + 1};
		if (x + 1 < n) {
			pair<int, int> b = get_down(x + 1, y, table[x][y + 1]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));		
		}
	}
	if (y - 1 >= 0) {
		pair<int, int> a = {x, y - 1};
		if (x + 1 < n) {
			pair<int, int> b = get_down(x + 1, y, table[x][y - 1]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));		
		}
	}
}

void solve_up(int x, int y, pair<ll, pair<pair<int, int> , pair<int, int>>> & ans) {
	if (y + 1 < m) {
		pair<int, int> a = {x, y + 1};
		if (x - 1 >= 0) {
			pair<int, int> b = get_up(x - 1, y, table[x][y + 1]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));	
		}
	}
	if (y - 1 >= 0) {
		pair<int, int> a = {x, y - 1};
		if (x - 1 >= 0) {
			pair<int, int> b = get_up(x - 1, y, table[x][y - 1]);
			ans = min(ans, make_pair(get(a, b), make_pair(a, b)));	
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	table.resize(n, vector<char> (m, ' '));
	for (auto &i : table)
		for (auto &j : i)
			cin >> j;
	
	int q;
	cin >> q;
	vector<pair<ll, pair<pair<int, int>, pair<int, int> > > > ans(q, {(ll)INF * INF, {}}); 
	vector<pair<int, int>> a(q);
	for (auto &i : a)
		cin >> i.first >> i.second;
	//cout << "puhh" << endl;
	build_up();
	for (int i = 0; i < q; i++) {
		solve_up(a[i].first - 1, a[i].second - 1, ans[i]);
	}
	//cout << "puhh" << endl;
	build_down();
	for (int i = 0; i < q; i++) {
		solve_down(a[i].first - 1, a[i].second - 1, ans[i]);
	}
	build_Left();
	for (int i = 0; i < q; i++) {
		solve_Left(a[i].first - 1, a[i].second - 1, ans[i]);
	}
	build_Right();
	for (int i = 0; i < q; i++) {
		solve_Right(a[i].first - 1, a[i].second - 1, ans[i]);
	}

	for (auto fans : ans) {
		if (fans.first > INF / 2) {
			cout << "-1\n";
		}
		else {
			cout << fans.second.first.first + 1 << " " << fans.second.first.second + 1 << " " << fans.second.second.first + 1 << " " << fans.second.second.second + 1 << "\n";
		}
	}
	return 0;
}