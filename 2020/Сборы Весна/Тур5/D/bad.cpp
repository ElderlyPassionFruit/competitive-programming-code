#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <random>

using namespace std;

// #define cerr if (false) cerr

const int N = 501;
const int INF = 2 * N;
const int K = 10;

int nx[K][N];
int dp[N][N];
int psum[N];

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][j] = INF;
		}
	}
}

int solve(vector<int> a, vector<int> sel) {
	// for (auto t : a) {
	// 	cerr << t;
	// }
	// cerr << endl;
	// for (auto t : sel) {
	// 	cerr << t;
	// }
	// cerr << endl;
	init();
	int n = (int)a.size();
	vector<int> psel;
	for (int i = 0; i < n; i++) {
		if (sel[i]) psel.push_back(i);
	}
	if (psel.empty()) return 0;
	// cerr << psel.size() << endl;
	for (int j = 0; j < K; j++) {
		nx[j][n - 1] = n;
		for (int i = n - 2; i >= 0; i--) {
			if (a[i + 1] == j) {
				nx[j][i] = i + 1;
			} else {
				nx[j][i] = nx[j][i + 1];
			}
		}
	}
	assert(sel[0] == 0);
	for (int i = 1; i < n; i++) {
		psum[i] = psum[i - 1] + sel[i];
	}
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] == INF) continue;
			if (j == (int)psel.size()) continue;
			// cerr << "hr " << i << ' ' << j << endl;
			int fr = i;
			int add = 0;
			if (psel[j] < i) {
				fr = psel[j];
				add += (i - psel[j]);
			}
			int alr = psum[i];
			// cerr << "wow" << endl;
			// if (i == 3 && j == 0) {
			// 	cerr << "alr: " << alr << endl;
			// 	cerr << "dp: " << dp[i][j] << endl;
			// 	cerr << "add: " << add << endl;
			// }
			for (int c = 0; c < K; c++) {
				// if (i == 3 && j == 0 && c == 5) {
				// 	cout << "nx" << endl;
				// 	cout << nx[c][fr] << endl;
				// 	cout << alr << endl;
				// }
				if (nx[c][fr] > i) dp[nx[c][fr]][alr] = min(dp[nx[c][fr]][alr], dp[i][j] + add + 2); 
			}
		}
	}
	// cout << dp[3][0] << endl;
	// cerr << n << ' ' << psum[n - 1] << endl;
	// cerr << dp[n][psum[n - 1]] << endl;
	int ans = dp[n][psum[n - 1]];
	return ans - 2;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string tmp = "abcdfghije";
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &t : a) {
		char c;
		cin >> c;
		for (int i = 0; i < 10; i++) {
			if (tmp[i] == c) t = i;
		}
		// cerr << t << ' ';
	}
	// cerr << endl;
	int all = 0;
	int p = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 9) all++;
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == 9) p++;
		else break;
	}
	vector<int> sel;
	vector<int> na;
	for (int i = 0; i < n; i++) {
		if (a[i] == 9) continue;
		if (i > 0 && a[i - 1] == 9) sel.push_back(1);
		else sel.push_back(0);
		na.push_back(a[i]);
	}
	sel[0] = 0;
	// cerr << all << ' ' << p << endl; 
	int add = 2 * all - p;
	// cerr << "solve" << endl;
	int ans = solve(na, sel);
	cout << ans + add << endl;
}
