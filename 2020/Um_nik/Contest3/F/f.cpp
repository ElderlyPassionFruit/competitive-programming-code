#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXLEN = 21, MAXADD = 10;
const int MAXCNT = 6;
vector<int> goodAns[MAXCNT * 7 + 1];
vector<int> nums = {0, 4, 7};
vector<int> good;

void buildGood() {
	for (int i0 = 0; i0 <= 2; i0++) {
		for (int i1 = i0; i1 <= 2; i1++) {
			for (int i2 = i1; i2 <= 2; i2++) {
				for (int i3 = i2; i3 <= 2; i3++) {
					for (int i4 = i3; i4 <= 2; i4++) {
						for (int i5 = i4; i5 <= 2; i5++) {
							int val = nums[i0] + nums[i1] + nums[i2] + nums[i3] + nums[i4] + nums[i5];
							goodAns[val] = {nums[i0], nums[i1], nums[i2], nums[i3], nums[i4], nums[i5]};
							good.push_back(val);
						}
					}
				}
			}
		}
	}
	sort(all(good));
	good.resize(unique(all(good)) - good.begin());
	/*cout << "good = " << endl;
	for (auto i : good) {
		cout << "val = " << i << " : ";
		for (auto x : goodAns[i]) {
			cout << x << " ";
		} 
		cout << endl;
	}
	cout << endl;*/
}

string make(string s) {
	reverse(all(s));
	while ((int)s.size() > 1 && s.back() == '0') {
		s.pop_back();
	}
	reverse(all(s));
	return s;
}

bool dp[MAXLEN][MAXLEN];
pair<int, int> par[MAXLEN][MAXLEN];

void solve() {
	for (int i = 0; i < MAXLEN; i++) {
		for (int j = 0; j < MAXADD; j++) {
			dp[i][j] = 0;
		}
	}
	string n;
	cin >> n;
	reverse(all(n));
	dp[0][0] = 1;
	for (int i = 0; i < (int)n.size(); i++) {
		for (int add = 0; add < MAXADD; add++) {
			if (!dp[i][add]) continue;
			for (int j = 0; j < (int)good.size(); j++) {
				int x = good[j];
				int val = (add + x) % 10;
				if (val != n[i] - '0') continue;
				int nxtAdd = (add + x) / 10;
				assert(nxtAdd < MAXADD);
				dp[i + 1][nxtAdd] = 1;
				par[i + 1][nxtAdd] = {j, add};
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i <= (int)n.size(); i++) {
		for (int j = 0; j < MAXADD; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/

	if (!dp[n.size()][0]) {
		cout << -1 << endl;
	} else {
		vector<string> ans(MAXCNT);
		int add = 0;
		for (int i = (int)n.size(); i > 0; i--) {
			for (int j = 0; j < MAXCNT; j++) {
				ans[j] += '0' + goodAns[good[par[i][add].first]][j];
			}
			add = par[i][add].second;
		}
		for (int i = 0; i < MAXCNT; i++) {
			cout << make(ans[i]) << " ";
		}
		cout << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	buildGood();
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}