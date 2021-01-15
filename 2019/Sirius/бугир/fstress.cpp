#include <bits/stdc++.h>

using namespace std;
#define int long long
string s;
void read() {
	cin >> s;
}
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;
int ans;
bool is_suff[MAXN];
int cnt[MAXN];
void run() {
	int n = s.length();
	is_suff[n] = 1;
	for (int i = n - 1; i >= 0; i--) {
		is_suff[i] = is_suff[i + 1] && (s[i] == '9');
	}

	int num = 0;
	for (int i = 1; i < n; i++) {
		num = num * 10 + (s[i - 1] - '0');
		//if (is_suff[i])
	//		num--;
		num %= MOD;
		num += MOD;
		num %= MOD;

		cnt[i] = num;

	//	if (is_suff[i])
	//		num++;
		num %= MOD;
		num += MOD;
		num %= MOD;
	}

	for (int i = n - 1; i >= 1; i--) {
		cnt[i] = cnt[i] - cnt[i - 1];
		cnt[i] %= MOD;
		cnt[i] += MOD;
		cnt[i] %= MOD;
	}

	cout << "cnt = " << endl;
	for (int i = 0; i < n; i++)
		cout << cnt[i] << " ";
	cout << endl;
	ans = 0;
	num = 0;
	for (int i = n - 1; i > 0; i--){
		num += 9;
		num %= MOD;
		ans += ((num - 1) * cnt[i]) % MOD;
		ans %= MOD;
	} 

	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += cnt[i];
		sum %= MOD;
	}

	num = 0;
	for (int i = 0; i < n; i++) {
		num *= 10;
		num += s[i] - '0';	
		num %= MOD;
	}
	num--;
	num %= MOD;
	num += MOD;
	num %= MOD;
	cout << "ans = " << ans << endl;
	cout << "num = " << num << " sum = " << sum << endl;
	num -= sum;
	num %= MOD;
	num += MOD;
	num %= MOD;
	cout << "num = " << num << " sum = " << sum << endl;
	ans += num;
	ans %= MOD;
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