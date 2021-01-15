#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 60;
int n;
int table[MAXN][MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> table[i][j];
		}
	}
}

pair <int, int> operator-(pair <int, int> a, pair <int, int> b) {
	return {a.first - b.first, a.second - b.second};
}

pair <int, int> operator+(pair <int, int> a, pair <int, int> b) {
	return {a.first + b.first, a.second + b.second};
}

pair <int, int> turn1(pair <int, int> a) {
	return {-a.second, a.first};
}

bool check(pair <int, int> a) {
	return a.first >= 1 && a.first <= n && a.second >= 1 && a.second <= n;
}

bool c(pair <int, int> a) {
	return table[a.first][a.second];
}

int check(pair <int, int> a, pair <int, int> b) {
	auto help = a - b;
	auto help1 = turn1(help);

	int ans = 0;

	auto x1 = b + help1;
	auto x2 = x1 + help;
	//cout << "x1 = " << x1.first << " " << x1.second << endl;
	//cout << "x2 = " << x2.first << " " << x2.second << endl;
	if (check(x1) && check(x2)) {
		ans += (c(a) == c(b)) && (c(x1) == c(a)) && (c(a) == c(x2));
		//ans++;
	}

	auto y1 = b - help1;
	auto y2 = y1 + help;
	//cout << "y1 = " << y1.first << " " << y2.second << endl;
	//cout << "y2 = " << y2.first << " " << y2.second << endl;
	if (check(y1) && check(y2)) {
		//ans++;
		ans += (c(a) == c(b)) && (c(a) == c(y1)) && (c(a) == c(y2));
	}
//	cout << ans << endl;
	return ans;
}


int ans = 0;

void run() {
//	cout << check({1LL, 2LL}, {2LL, 2LL}) << endl;
//	return;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				for (int l = 1; l <= n; l++) {
					if (i == k && j == l) continue;
					//if (check({i, j}, {k, l})) {
					//	cout << i << " " << j << " " << k << " " << l << " " << check({i, j}, {k, l}) << endl;
					//}
					ans += check({i, j}, {k, l});
				}
			}
		}
	}
	ans /= 8;
}

void write() {
	cout << ans << endl;
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