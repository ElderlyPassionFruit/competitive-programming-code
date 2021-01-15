#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10, MAXLEN = 1e6, MAXK = 26;
int cnt[MAXLEN][MAXK];
string s[MAXN];
int n;

void add(int i) {
	for (int j = 0; j < s[i].size(); j++) {
		cnt[j][s[i][j] - 'a']++;
	} 
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		add(i);
	}
	int ans = 0;
	for (int i = 0; i < MAXLEN; i++) {
		int sum = 0, mx = 0;
		for (int j = 0; j < MAXK; j++) {
			sum += cnt[i][j];
			mx = max(mx, cnt[i][j]);
		}
		ans += sum - mx;
	}
	cout << ans << endl;
	return 0;
}