#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


struct event{
	int d, m, a, ind;
	event() {}
	event(int x, int y, int z, int t) {
		d = x, m = y, a = z, ind = t;
	}
};

bool operator==(const event & a, const event & b) {
	return tie(a.d, a.m, a.a, a.ind) == tie(b.d, b.m, b.a, b.ind);
}

bool operator<(const event & a, const event & b) {
	return tie(a.d, a.m, a.a, a.ind) < tie(b.d, b.m, b.a, b.ind);
}

int n;
vector<event> arr;

void read() {
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].d >> arr[i].m >> arr[i].a;
		arr[i].ind = i;
	}
}

void build() {
	vector<event> ans;
	sort(all(arr), [&] (event i, event j) {return i.d > j.d;});
	for (int i = 0; i < min(100LL, (int)arr.size()); i++) {
		ans.push_back(arr[i]);
	}
	sort(all(arr), [&] (event i, event j) {return i.m > j.m;});
	for (int i = 0; i < min(100LL, (int)arr.size()); i++) {
		ans.push_back(arr[i]);
	}
	sort(all(arr), [&] (event i, event j) {return i.a > j.a;});
	for (int i = 0; i < min(100LL, (int)arr.size()); i++) {
		ans.push_back(arr[i]);
	}
	sort(all(ans));	
	ans.resize(unique(all(ans)) - ans.begin());
	arr = ans;
	n = arr.size();
}

const int MAXN = 1000, MAXD = 6, MAXM = 4, MAXA = 3;

int dp[MAXN][MAXD][MAXM][MAXA];
int par[MAXN][MAXD][MAXM][MAXA];

void calc() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXD; j++)
			for (int k = 0; k < MAXM; k++)
				for (int l = 0; l < MAXA; l++)
					dp[i][j][k][l] = -1e18;
	dp[0][0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int d = 0; d < MAXD; d++) {
			for (int m = 0; m < MAXM; m++) {
				for (int a = 0; a < MAXA; a++){
					dp[i][d][m][a] = dp[i - 1][d][m][a];
					par[i][d][m][a] = 0;
					if (d > 0 && dp[i - 1][d - 1][m][a] >= 0) {
						if (dp[i][d][m][a] < dp[i - 1][d - 1][m][a] + arr[i - 1].d) {
							dp[i][d][m][a] = dp[i - 1][d - 1][m][a] + arr[i - 1].d;
							par[i][d][m][a] = 1;		
						}
					}
					if (m > 0 && dp[i - 1][d][m - 1][a] >= 0) {
						if (dp[i][d][m][a] < dp[i - 1][d][m - 1][a] + arr[i - 1].m) {
							dp[i][d][m][a] = dp[i - 1][d][m - 1][a] + arr[i - 1].m;
							par[i][d][m][a] = 2;		
						}
					}
					if (a > 0 && dp[i - 1][d][m][a - 1] >= 0) {
						if (dp[i][d][m][a] < dp[i - 1][d][m][a - 1] + arr[i - 1].a) {
							dp[i][d][m][a] = dp[i - 1][d][m][a - 1] + arr[i - 1].a;
							par[i][d][m][a] = 3;		
						}
					}
				}
			}
		} 
	}
}

vector<int> ansD, ansM, ansA;

void make_ans() {
	int pos = n, d = 5, m = 3, a = 2;
	while ((d > 0 || m > 0 || a > 0)) {
		if (par[pos][d][m][a] == 0) {
			pos--;
			continue;
		}
		if (par[pos][d][m][a] == 1) {
			ansD.push_back(arr[pos - 1].ind);
			pos--;
			d--;
			continue;
		}
		if (par[pos][d][m][a] == 2) {
			ansM.push_back(arr[pos - 1].ind);
			pos--;
			m--;
			continue;
		}
		if (par[pos][d][m][a] == 3) {
			ansA.push_back(arr[pos - 1].ind);
			pos--;
			a--;
			continue;
		}
	}
}

void run() {
	build();
	calc();
	make_ans();
}

void write() {
	sort(all(ansD));
	for (auto i : ansD)
		cout << i + 1 << " ";
	cout << endl;
	sort(all(ansM));
	for (auto i : ansM)
		cout << i + 1 << " ";
	cout << endl;
	sort(all(ansA));
	for (auto i : ansA)
		cout << i + 1 << " ";
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