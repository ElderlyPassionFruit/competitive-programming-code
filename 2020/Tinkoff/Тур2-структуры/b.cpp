#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e10 + 10;

const int MAXN = 510;
int n, m;
int a[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
}

const int MAXLOG = 10;
int sparse[MAXN][MAXN][MAXLOG][MAXLOG];
int lg[MAXN];
int pows[MAXLOG];

void build() {
	pows[0] = 1;
	for (int i = 1; i < MAXLOG; i++)
		pows[i] = pows[i - 1] * 2;
	for (int i = 2; i < MAXN; i++)
		lg[i] = lg[i / 2] + 1;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			sparse[i][j][0][0] = a[i][j];

	for (int log = 1; log <= lg[m]; log++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (j + pows[log - 1] < m)
					sparse[i][j][0][log] = min(sparse[i][j][0][log - 1], sparse[i][j + pows[log - 1]][0][log - 1]); 

	for (int k1 = 1; k1 <= lg[n]; k1++)
		for (int i = 0; i < n; i++)
			for (int k2 = 0; k2 <= lg[m]; k2++)
				for (int j = 0; j < m; j++)
					if (i + pows[k1 - 1] < n)
						sparse[i][j][k1][k2] = min(sparse[i][j][k1 - 1][k2], sparse[i + pows[k1 - 1]][j][k1 - 1][k2]);
}

int get(int x1, int y1, int x2, int y2) {
	int k1 = lg[x2 - x1 + 1];
	int k2 = lg[y2 - y1 + 1];
	int ans = INF;
	chkmin(ans, sparse[x1][y1][k1][k2]);
	chkmin(ans, sparse[x2 - pows[k1] + 1][y2 - pows[k2] + 1][k1][k2]);
	chkmin(ans, sparse[x2 - pows[k1] + 1][y1][k1][k2]);
	chkmin(ans, sparse[x1][y2 - pows[k2] + 1][k1][k2]);
	return ans;
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--;
		y1--;
		x2--;
		y2--;
		int fans = get(x1, y1, x2, y2);
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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