#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m, mod;
const int MAXN = 2*1e4 + 10;
int N[MAXN], M[MAXN];

void read() {
	cin >> n >> m >> mod;
	for (int i = 0; i < n; i++) {
		cin >> N[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> M[i];
	}
}

vector <pair <int, int> > ans;
int dp[MAXN];

int f(int a, int b) {
//	cout << "a = " << a << " b = " << b << " N[a] = " << N[a] << " M[b] = " << M[b] << endl;
	return (N[a] + M[b]) % mod;
}

void w() {
	cout << "puhh" << endl;
}

void clear() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = 0;
}

void go(int l_n, int r_n, int l_m, int r_m) {
	if (l_n > r_n || l_m > r_m)
		return;
	/*if ((r_n - l_n <= 1 && r_m - l_n == 0) || (r_n - l_n <= 1 && r_m - l_n == 0) || (r_n == l_n && r_m == l_m)) {
		for (int i = l_n; i <= r_n; i++) {
			for (int j = l_m; j <= r_m; j++) {
				ans.push_back({i, j});
			}
		}
		return;
	}*/	
	cout << "l_n = " << l_n << " r_n = " << r_n << " l_m = " << l_m << " r_m = " << r_m << endl;
	int len = (r_n - l_n + r_m - l_m) / 2;
	set <pair <int, int> > help;
	for (int i = l_n; i <= r_n; i++) {
		for (int j = l_m; j <= r_m; j++) {
			if (i + j == l_n + l_m + len)
			help.insert({i, j});
		}
	}
	
	map <pair <int, int> , int> fans;
	for (int j = l_m; j <= r_m; j++) {
		for (int i = l_n; i <= r_n; i++) {
			if (i == l_n && j == r_n)
				continue;
			dp[i] += f(i, j);
			if (i > 0) dp[i] = max(dp[i], dp[i - 1] + f(i, j));
			if (help.find({i, j}) != help.end()) {
				fans[{i, j}] += dp[i];
				break;
			}
		}
	}

	for (int j = r_m; j >= l_m; j--) {
		for (int i = r_n; i >= l_n; i--) {
			if (i == r_n && j == l_n)
				continue;
			if (help.find({i, j}) != help.end()) {
				fans[{i, j}] += max(dp[i], dp[i + 1]);
				break;
			}
			dp[i] = max(dp[i], dp[i + 1]) + f(i, j);
		}
	}

	if (fans.size() == 0)
		return;

	pair <int, int> x;
	int cost = 0;

	for (auto i : fans) {
		if (i.second > cost) {
			cost = i.second;
			x = i.first;
		}
	}

	ans.push_back(x);
	go(l_n, x.first, l_m, x.second);
	go(x.first, r_n, x.second, r_m);

}

string fout;
void run() {
	go(0, n - 1, 0, m - 1);
	fout = "";
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].first << " " << ans[i].second << endl;
	}
}

void write() {
//	cout << ans1 << endl;
	cout << fout << endl;
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