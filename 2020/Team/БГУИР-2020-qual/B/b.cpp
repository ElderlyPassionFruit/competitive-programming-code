#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
void no() {
	cout << "-1 -1";
	exit(0);
}

const ll INF = 1000000000000000000;
	
int make(vector<int> cnt) {
	int sum = 0;
	for (auto i : cnt)
		sum += i;
	if (cnt[0] == sum && sum > 1) no();
	ll ans = 0;
	for (int i = 1; i <= 9; i++) {
		if (cnt[i]) {
			cnt[i]--;
			ans = i;
			break;
		}
	}
	for (int i = 0; i <= 9; i++) {
		while (cnt[i]--) {
			ans *= 10;
			ans += i;
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	vector<int> cnt(10);
	int n = s.size();
	if (n == 1) no();
	for (auto i : s) cnt[i - '0']++;
	if (n > 38) no();
	if (n == 38) {
		if (cnt[0] == 36 && cnt[1] == 2) {
			cout << INF << " " << INF << endl;
			return 0;
		}
		no();
	}

	if (cnt[0] >= 18 && cnt[1] >= 1 && n > 19) {
		cnt[0] -= 18;
		cnt[1]--;
		int fans = make(cnt);
		cout << fans << " " << INF << endl;
		return 0;
	}

	if (n > 36) no();
	int len = max(1LL, n - 18);

	if (len == 1) {
		int fans = 0;
		for (int i = 0; i <= 9; i++) {
			if (cnt[i]) {
				cnt[i]--;
				fans = i;
				break;
			}
		}
		int ans = make(cnt);
		cout << fans << " " << ans << endl;
	}
	else {
		int fans = 0;
		bool flag = false;
		for (int i = 1; i <= 9; i++) {
			if (cnt[i]) {
				cnt[i]--;
				flag = true;
				fans = i;
				len--;
				break;
			}
		}
		if (!flag) no();
		for (int i = 0; i <= 9; i++) {
			while (cnt[i] && len > 0) {
				cnt[i]--;
				fans *= 10;
				fans += i;
				len--;
			}
		}
		int ans = make(cnt);
		cout << fans << " " << ans << endl;
	}
	return 0;
}