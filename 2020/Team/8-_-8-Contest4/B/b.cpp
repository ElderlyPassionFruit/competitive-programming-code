#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 20;
int n, k;
string last[MAXN];
string myLast[MAXN];

bool check(int mask) {
	int sum = k;
	for (int i = 0; i < k; i++) {
		sum -= (mask >> i) & 1;
		sum--;
		if (sum == 0) break;
		if (sum < 0) return false;
	}
	return sum == 0;
}

char solve(string & my, string & bot) {
	for (int i = 0; ; i++) {
		if (i == (int)my.size()) return 'W';
		if (i == (int)bot.size()) return 'W';
		if (my[(int)my.size() - 1 - i] == bot[(int)bot.size() - 1 - i]) continue;
		return bot[(int)bot.size() - 1 - i];
	}
	assert(false);
	return '-';
}

char getOther(char x) {
	if (x == 'W') return 'B';
	return 'W';
}

int solve(int mask) {
	if (!check(mask)) {
		return 0;
	}
	for (int i = 0; i < n; i++) {
		myLast[i] = last[i];
	}
	string now = "";
	int sum = k;
	int ans = 0;
	//cout << "mask = ";
	for (int i = 0; i < k; i++) {
	//	cout << 1 + ((mask >> i) & 1) << " ";
		for (int j = 0; j <= ((mask >> i) & 1); j++) {
			char t = solve(now, last[i % n]);
			if (t == 'W') ans++;
			now += t;
			last[i % n] += getOther(t);
		}
		sum -= 1 + ((mask >> i) & 1);
		if (sum == 0) break;
	}
	//cout << endl;
	//cout << "last = " << endl;
	//for (int i = 0; i < n; i++) {
	//	cout << last[i] << " ";
	//}
	//cout << endl;
	//cout << "now = " << now << endl;
	//if (ans == 4) {
	//	cout << "bad = " << mask << endl; 
	//}
	for (int i = 0; i < n; i++) {
		last[i] = myLast[i];
	}
	return ans;
}

signed main() {
	freopen("checkers.in", "r", stdin);
	freopen("checkers.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> last[i];
	}
	//cout << solve(0) << endl;
	//exit(0);
	int ans = 0;
	for (int mask = 0; mask < (1 << k); mask++) {
		ans = max(ans, solve(mask));
	} 
	cout << ans << endl;
	return 0;
}