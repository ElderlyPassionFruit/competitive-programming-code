#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 1e9 + 7;

int n, f1, f2, f3, c;
void read() {
	//cin >> n >> f1 >> f2 >> f3 >> c;
}


int dp[1000];
void run() {
	dp[1] = 1;
	dp[2] = 3;
	dp[3] = 7;
	for (int i = 4; i < 100; i++) {
		dp[i] = dp[i - 1] + 1 + dp[i - 1] + dp[i - 2] + dp[i - 3];
	}
	for (int i = 0; i < 20; i++)
		cout << dp[i] * 2 << " ";
	cout << endl;
}

void write() {

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