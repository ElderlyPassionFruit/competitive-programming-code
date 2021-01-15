#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, a, b, c;
const int MAXA = 2;

void read() {
	cin >> n >> a >> b >> c;
	chkmin(a, MAXA - 1);
	chkmin(b, MAXA - 1);
	chkmin(c, MAXA - 1);
}

void no() {
	cout << "No\n";
	exit(0);
}

vector<char> ans;

const int MAXN = 1e5 + 10;

bool dp[MAXN][MAXA][MAXA][MAXA];
pair<int, int> par[MAXN][MAXA][MAXA][MAXA];

void run() {
	dp[0][a][b][c] = 1;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int a = 0; a < MAXA; a++) {
			for (int b = 0; b < MAXA; b++) {
				for (int c = 0; c < MAXA; c++) {
					if (!dp[i][a][b][c]) continue;	
					if (s == "AB") {
						if (a > 0) {
							dp[i + 1][a - 1][min(b + 1, MAXA - 1)][c] = 1;
							par[i + 1][a - 1][min(b + 1, MAXA - 1)][c] = {2, 1};
							if (b == MAXA - 1) 
								par[i + 1][a - 1][min(b + 1, MAXA - 1)][c].first = -2;
						}
						if (b > 0) {
							dp[i + 1][min(a + 1, MAXA - 1)][b - 1][c] = 1;
							par[i + 1][min(a + 1, MAXA - 1)][b - 1][c] = {1, 2};
							if (a == MAXA - 1)
								par[i + 1][min(a + 1, MAXA - 1)][b - 1][c].first = -1;
						}
					} else if (s == "BC") {
						if (c > 0) {
							dp[i + 1][a][min(b + 1, MAXA - 1)][c - 1] = 1;
							par[i + 1][a][min(b + 1, MAXA - 1)][c - 1] = {2, 3};
							if (b == MAXA - 1)
								par[i + 1][a][min(b + 1, MAXA - 1)][c - 1].first = -2;
						}
						if (b > 0) {
							dp[i + 1][a][b - 1][min(c + 1, MAXA - 1)] = 1;
							par[i + 1][a][b - 1][min(c + 1, MAXA - 1)] = {3, 2};
							if (c == MAXA - 1)
								par[i + 1][a][b - 1][min(c + 1, MAXA - 1)].first = -3;
						}
					} else if (s == "AC") {
						if (a > 0) {
							dp[i + 1][a - 1][b][min(c + 1, MAXA - 1)] = 1;
							par[i + 1][a - 1][b][min(c + 1, MAXA - 1)] = {3, 1};
							if (c == MAXA - 1)
								par[i + 1][a - 1][b][min(c + 1, MAXA - 1)].first = -3;
						}
						if (c > 0) {
							dp[i + 1][min(a + 1, MAXA - 1)][b][c - 1] = 1;
							par[i + 1][min(a + 1, MAXA - 1)][b][c - 1] = {1, 3};
							if (a == MAXA - 1)
								par[i + 1][min(a + 1, MAXA - 1)][b][c - 1].first = -1;
						}
					} else {
						assert(false);
					}
				}
			}
		}
	}

	int A = -1, B = -1, C = -1;
	for (int a = 0; a < MAXA; a++) {
		for (int b = 0; b < MAXA; b++) {
			for (int c = 0; c < MAXA; c++) {
				if (dp[n][a][b][c]) {
					A = a;
					B = b;
					C = c;
				}
			}
		}
	}
	if (A == -1) no();
	for (int i = n; i > 0; i--) {
		assert(dp[i][A][B][C]);
		int add = par[i][A][B][C].first;
		int del = par[i][A][B][C].second;
		if (add == 1) A--, ans.push_back('A');
		else if (add == 2) B--, ans.push_back('B');
		else if (add == 3) C--, ans.push_back('C');
		else if (add == -1) ans.push_back('A');
		else if (add == -2) ans.push_back('B');
		else if (add == -3) ans.push_back('C');
		if (del == 1) A++;
		else if (del == 2) B++;
		else if (del == 3) C++;
		chkmin(A, MAXA - 1);
		chkmin(B, MAXA - 1);
		chkmin(C, MAXA - 1);
	}
	reverse(all(ans));
}

void write() {
	cout << "Yes\n";
	for (auto i : ans) {
		cout << i << "\n";
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