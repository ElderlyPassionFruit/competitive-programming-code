#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, a, b;
string s;

void read() {
	cin >> n >> a >> b >> s;
}

const int MAXN = 5010;
int ans = 0;
int dp[MAXN];

vector<int> z_function(string s) {
	vector <int> z(s.length());
	int l = 0, r = 0;
	for (int i = 1; i < s.length(); i++) {
		if (i <= r) 
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] > r) 
			l = i, r = i + z[i] - 1;
	}
	return z;
}

const int INF = 1e18;
void run() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = INF;
	
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = min(dp[i], dp[i - 1] + a);
		
		string help = "";
		for (int j = 0; j < i; j++) help += s[j];
		reverse(help.begin(), help.end());
		auto fans = z_function(help);
		
		int mx = 0;
		for (int j = 0; j < i; j++) {
			mx = max(mx, min(fans[j], j));
		}
		
		for (int j = 1; j <= mx; j++) {
			dp[i] = min(dp[i], dp[i - j] + b);
		}
	}
//	cout << "dp = " << endl;
//	for (int i = 0; i <= n; i++)
//		cout << dp[i] << " ";
//	cout << endl;
	ans = dp[n];
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