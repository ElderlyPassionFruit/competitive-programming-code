//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e3 + 10;
int n, k;
int a[MAXN][MAXN];

inline void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
}

struct event{
	int x1, y1, x2, y2, cost;
};

inline bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

int cur = 0;
int used[MAXN][MAXN];

inline bool check(const vector<int> & mask, const vector<event> & q) {
	cur++;
	for (int i = 0; i < q.size(); i++) {
		if (mask[i]) {
			if (used[q[i].x1][q[i].y1] == cur || used[q[i].x2][q[i].y2] == cur)
				return false;
			used[q[i].x1][q[i].y1] = cur;
			used[q[i].x2][q[i].y2] = cur;
		}
	} 
	return true;
}

inline int get(const vector<int> & mask, const vector<event> & q) {
	if (!check(mask, q)) return 0;
	int ans = 0;
	for (int i = 0; i < q.size(); i++) {
		if (mask[i]) {
			ans += q[i].cost;
		}
	}
	return ans;
}

long long ans;
double st;

inline void run() {
	ans = 0;
	vector<event> q;
	vector<int> dx = {0, 1}, dy = {1, 0};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < 2; k++) {
				if (!check(i + dx[k], j + dy[k])) continue;
				q.push_back({i, j, i + dx[k], j + dy[k], a[i][j] + a[i + dx[k]][j + dy[k]]});
			}
		}
	}
	sort(q.begin(), q.end(), [&] (event a, event b) {return a.cost > b.cost;});

	int cnt = 0;
	chkmin(k, q.size());
	for (int i = 1; i <= k; i++) {
		vector<int> mask(q.size());
		for (int j = 0; j < i; j++) 
			mask[q.size() - 1 - j] = 1;
		do {
			chkmax(ans, get(mask, q));
		} while (next_permutation(mask.begin(), mask.end()));
	}

	long long sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sum += a[i][j];
		}
	}
	ans = sum - ans;
}

inline void write() {
	cout << ans << endl;
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);  
	st = clock();
	read();
	run();
	write();
	return 0;
}