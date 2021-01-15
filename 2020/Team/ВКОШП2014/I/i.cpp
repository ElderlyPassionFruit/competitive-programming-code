#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int w, h, n, q;
int bad = 0;

const int MAXN = 1e5 + 10;
set<int> have_x[MAXN], have_y[MAXN];

bool check_x(int x) {
	if (have_y[x].empty()) return true;
	return *(--have_y[x].end()) - *(have_y[x].begin()) + 1 == (int)have_y[x].size();
}

bool check_y(int y) {
	if (have_x[y].empty()) return true;
	return *(--have_x[y].end()) - *(have_x[y].begin()) + 1 == (int)have_x[y].size();
}

void add(int x, int y) {
	if (!check_x(x)) bad--;
	if (!check_y(y)) bad--;
	have_x[y].insert(x);	
	have_y[x].insert(y);
	if (!check_x(x)) bad++;
	if (!check_y(y)) bad++;
}

void check() {
	if (bad == 0) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	cout << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("turtles.in", "r", stdin);
	freopen("turtles.out", "w", stdout);
	cin >> w >> h >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		add(x, y);
	}
	check();
	cin >> q;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		add(x, y);
		check();
	}
	return 0;
}

/*

5 10
8
1 4
2 4
2 5
2 6
1 6
3 5
3 4
4 4
4
1 5
2 7
3 7
3 6

*/