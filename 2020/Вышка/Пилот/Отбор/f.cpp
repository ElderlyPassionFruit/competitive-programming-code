#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll
const int N = 110;
int n, k, realK;
int a[N];

void read() {
	cin >> n >> k;
	realK = k;
	chkmin(k, n);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
}

int dp[N][N];
int par[N][N];

void relax(int pos, int cnt, int val, int fpar) {
	if (dp[pos][cnt] >= val) return;
	dp[pos][cnt] = val;
	par[pos][cnt] = fpar;
}

void calcDp() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		relax(i, 1, a[i], -1);
		for (int cnt = 2; cnt <= k; cnt++) {
			for (int prev = 1; prev < i; prev++) {
				if (dp[prev][cnt - 1] == -1) continue;
				int cost = dp[prev][cnt - 1] + a[i] + a[prev] * (i - prev - 1);
				relax(i, cnt, cost, prev);
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/
}

vector<int> ans;

void makeAns() {
	int myPos = 0;
	for (int i = 1; i <= n; i++) {
		if (dp[myPos][k] + (n - myPos) * a[myPos] <= dp[i][k] + (n - i) * a[i]) {
			myPos = i;
		}
	}
	int cnt = k;
	while (myPos != -1) {
		ans.push_back(a[myPos]);
		myPos = par[myPos][cnt];
		cnt--;	
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	while (ans.size() < realK) {
		ans.push_back(ans.back() + 1);
	}
}

void run() {
	calcDp();
	makeAns();
}

void write() {
	for (int i = 0; i < realK; i++) {
		cout << ans[i] << " ";
	}
	cout << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}