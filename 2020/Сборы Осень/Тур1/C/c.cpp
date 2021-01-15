#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110;

struct event{
	int p, r, q, f;
	event() {}
};

struct p{
	int my, last;
	p() {}
	p(int a, int b) {
		my = a, last = b;
	}
};

int dp[MAXN][MAXN];
p par[MAXN][MAXN];

int n, l;
vector<event> a;

void read() {
	cin >> n >> l;
	a.resize(n);
	for (auto &i : a)
		cin >> i.p >> i.r >> i.q >> i.f;
}

const int INF = 1e18;

void calc() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= l; j++) {
			
			dp[i][j] = dp[i - 1][j];
			par[i][j] = {0, j};
			
			for (int k = 0; k < j; k++) {
				
				if (dp[i - 1][k] == INF) continue;
				int need = j - k;
				
				if (need > a[i - 1].f) continue;
				
				
				if (need >= a[i - 1].r) {
					int cost = need * a[i - 1].q;
					if (dp[i][j] > dp[i - 1][k] + cost) {
						dp[i][j] = dp[i - 1][k] + cost;
						par[i][j] = {need, k};
					}
				}
				else {
					int cost = need * a[i - 1].p;
					if (dp[i][j] > dp[i - 1][k] + cost) {
						dp[i][j] = dp[i - 1][k] + cost;
						par[i][j] = {need, k};
					}
					
					need = a[i - 1].r;
					if (need > a[i - 1].f) continue;
					cost = need * a[i - 1].q;
					if (dp[i][j] > dp[i - 1][k] + cost) {
						dp[i][j] = dp[i - 1][k] + cost;
						par[i][j] = {need, k};
					}
				}
			}
		}
	}
}

vector<int> ans;

void make_ans() {
	if (dp[n][l] == INF) {
		cout << -1 << endl;
		exit(0);
	}
	ans.resize(n);
	int pos = n, have = l;
	
	while (pos > 0) {
		ans[pos - 1] = par[pos][have].my;
		have = par[pos][have].last;
		pos--;
	}
}

void run() {
	calc();
	make_ans();
}

void write() {
	cout << dp[n][l] << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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