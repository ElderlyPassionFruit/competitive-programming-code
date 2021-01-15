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

int run(string s) {
	int ans = 0;
	for (int i = 0; i < MAXN; i++) {
		cnt[i] = 0;
		is_suff[i] = false;
		ans = 0;
	}

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

	/*cout << "cnt = " << endl;
	for (int i = 0; i < n; i++)
		cout << cnt[i] << " ";
	cout << endl;*/
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
	//cout << "num = " << num << " sum = " << sum << endl;
	num -= sum;
	num %= MOD;
	num += MOD;
	num %= MOD;
	//cout << num << endl;
	//cout << ans << endl;
	ans += num;
	ans %= MOD;
	return ans;
}



int get(int x) {
	int ans = 0;
	while (x) {
		ans += x % 10;
		x /= 10;
	}
	return ans;
}

int run2(int n) {
	int ans = 0;
	for (int i = 1; i < n; i++) {
		ans += abs(get(i) - get(i + 1));
		ans %= MOD;
	}
	return ans;
}

pair <string, int> gen() {
	int n = rand() % 100000 + 1;
	int n1 = n;
	string x = "";
	while (n) {
		x += ((n % 10) + '0');
		n /= 10;
	}
	reverse(x.begin(), x.end());
	return {x, n1};
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	for (int test = 0; test < 10000; test++) {
		auto x = gen();
		int ans1 = run(x.first);
		int ans2 = run2(x.second);
		if (ans1 != ans2) {
			cout << "WA " << test << endl;
			cout << x.first << " " << x.second << endl;
			cout << ans1 << " " << ans2 << endl;
			return 0;
		}
		cout << "OK " << test << endl;

	}
	return 0;
}