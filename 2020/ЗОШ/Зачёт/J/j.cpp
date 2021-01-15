#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 2e5 + 10;
int a[MAXN];
int pref[MAXN];
pair<int, int> dp[MAXN];
int n, m;

struct segment{
	int l, r;
	segment() {
	}
	segment(int a, int b) {
		l = a, r = b;
	}
};

vector<segment> have;

void chkmax(pair<int, int> & a, pair<int, int> b) {
	a = max(a, b);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	pref[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pref[i] = pref[i - 1] + a[i];
	}
	/*cout << "pref = " << endl;
	for (int i = 0; i <= n; i++)
		cout << pref[i] << " ";
	cout << endl;*/

	cin >> m;
	have.resize(m);
	for (int i = 0; i < MAXN; i++)
		dp[i] = {-1e18, -1e18};
	int ind = 0;
	for (auto &i : have) { 
		cin >> i.l >> i.r;
		chkmax(dp[i.r], make_pair(pref[i.r] - pref[i.l - 1], ind));
		ind++;
	}
	for (int i = 1; i < MAXN; i++)
		chkmax(dp[i], dp[i - 1]);

	/*cout << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		cout << dp[i].first << " " << dp[i].second << endl;
	}
	cout << endl;*/
	int ans = -1e18;
	int pos1 = -1, pos2 = -1;
	ind = 0;
	for (auto i : have) {
		if (dp[i.l - 1].first == -1e18) {
			ind++;
			continue;
		}
		int fans = dp[i.l - 1].first + pref[i.r] - pref[i.l - 1];
		if (ans < fans) {
			//cout << i.l << " " << i.r << endl;
			//cout << ans << " " << fans << " " << ind << " " << dp[i.l - 1].second << endl;
			ans = fans;
			pos1 = ind;
			pos2 = dp[i.l - 1].second;
		}
		ind++;
	}

	if (ans == -1e18) {
		cout << "-1 -1" << endl;
	}
	else {
		if (pos1 > pos2)
			swap(pos1, pos2);
		cout << pos1 + 1 << " " << pos2 + 1 << endl;
	}
	return 0;
}



















