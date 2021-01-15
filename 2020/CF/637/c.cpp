#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXM = 200;
int n, m, g, r;
int d[MAXM];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> d[i];
	}	
	sort(d + 1, d + m + 1);
	cin >> g >> r;
}

const int MAXG = 1010;
bitset<MAXG> can[MAXM];

void precalc() {
	for (int i = 0; i < MAXM; i++) {
		for (int j = 0; j < MAXG; j++) {
			can[i][j] = 0;
		}
	}
	for (int i = 1; i <= m; i++) {
		can[i][0] = 1;
	}

	for (int dist = 1; dist <= g; dist++) {
		for (int i = 1; i <= m; i++) {
			int len;
			len = abs(d[i] - d[i - 1]) * 2;
			if (i > 1 && dist - len >= 0) {
				if (can[i - 1][dist - len]) {
					can[i][dist] = 1;
				}
			}
			len = abs(d[i + 1] - d[i]) * 2;
			if (i < m && dist - len >= 0) {
				if (can[i + 1][dist - len])
					can[i][dist] = 1;
			}
		}
	}

	/*cout << "can = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= g; j++) {
			cout << can[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
}

const int INF = 1e18 + 10;
int dist[MAXM];
int ans;

bitset<MAXG> used;

void calc() {
	for (int i = 0; i < MAXM; i++) {
		dist[i] = INF;
	}
	queue<int> q;
	dist[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		used = can[v];
		for (int i = v + 1; i <= m; i++) {
			used |= used << abs(d[v] - d[i]);
			used |= can[i];

			if (abs(d[i] - d[v]) > g) break;
			if (dist[i] <= dist[v] + 1) continue;
			if (!used[g - abs(d[i] - d[v])]) continue;
			dist[i] = dist[v] + 1;
			q.push(i);
		}
		used = can[v];
		for (int i = v - 1; i >= 1; i--) {
			used |= used << abs(d[v] - d[i]);
			used |= can[i];
			if (abs(d[v] - d[i]) > g) break;
			if (dist[i] <= dist[v] + 1) continue;
			if (!used[g - abs(d[i] - d[v])]) continue;
			dist[i] = dist[v] + 1;
			q.push(i);
		}
	}

	cout << "dist = " << endl;
	for (int i = 1; i <= m; i++) {
		cout << d[i] << " " << dist[i] << endl;
	}
	cout << endl;

	ans = INF;
	for (int i = 1; i <= m; i++) {
		int len = abs(n - d[i]);
		if (len > g) continue;
		if (dist[i] == INF) continue;
		chkmin(ans, dist[i] * (g + r) + len);
	}

	if (ans == INF) {
		ans = -1;
	}

	/*if (dist[m] == INF) {
		cout << -1 << endl;
	} else {
		ans = dist[m] * g + max(0LL, dist[m] - 1) * r;
	}*/
}

void run() {
	precalc();
	calc();
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


/*
WA 2
input = 
10 6
0 10 4 6 3 9 
4 5

ans = 
22

out = 
-1


input = 
7 5
0 7 4 2 1 
5 5

ans = 
23

out = 
25


WA 110
input = 
17 9
0 17 2 10 13 11 7 9 3 
15 16

ans = 
35

out = 
37

input = 
88 24
0 88 44 8 30 71 40 56 17 52 78 79 34 86 77 26 37 87 16 31 29 24 46 18 
19 19

ans = 
207

out = 
-1

WA 526
input = 
45 8
0 45 41 20 22 3 31 40 
33 36

ans = 
161

out = 
163

*/