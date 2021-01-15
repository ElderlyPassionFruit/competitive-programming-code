#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 7010, MAXK = 30001;
int dp[MAXK];
int n, k;
int a[MAXN * 2];
bool used[MAXN * 2];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 1; i <= 2 * n; i++) {
		cin >> a[i];
	}

	vector<pair<int, int>> have;
	for (int i = 2; i + 1 <= 2 * n; i += 2) {
		have.push_back({a[i + 1] - a[i], i});
	}
	int need = (a[2 * n] - a[1]) - k;
	if (need < 0) {
		//assert(false);
		cout << "No" << "\n";
		return 0;
	}
	if (need == 0) {
		//assert(false);
		cout << "Yes" << "\n";
		for (int i = 1; i <= n; i++) {
			cout << i << " " << 2 * n - i + 1 << "\n";
		}
		return 0;
	}
	//cout << "need = " << need << endl; 
	//cout << "have = " << endl;
	//for (auto i : have)
	//	cout << i.first << " " << i.second << endl;

	//sort(all(have));
	for (int i = 0; i < MAXK; i++)
		dp[i] = -1;
	dp[0] = 0;

	for (int i = 0; i < have.size(); i++) {
		for (int j = need; j - have[i].first >= 0; j--) {
			if (dp[j - have[i].first] == -1) continue;
			if (dp[j] != -1) continue;
			dp[j] = i;
		}
	}

	if (dp[need] == -1) {
		//assert(false);
		cout << "No" << endl;
		return 0;
	}

	vector<int> fans;
	int pos = need;
	while (pos) {
		fans.push_back(have[dp[pos]].second);
		fans.push_back(fans.back() + 1);
		pos -= have[dp[pos]].first;
	}
	fans.push_back(1);
	fans.push_back(2 * n);
	sort(all(fans));
	fans.resize(unique(all(fans)) - fans.begin());
	vector<pair<int, int> > ans;
	assert(fans.size() % 2 == 0);
	for (int i = 0; i + 1 < fans.size(); i += 2) {
		ans.push_back({fans[i], fans[i + 1]});
	}
	
	for (int i = 0; i < 2 * MAXN; i++)
		used[i] = false;
	
	for (auto i : ans)
		used[i.first] = true, used[i.second] = true;
	
	for (int i = 1; i <= 2 * n; i++) {
		if (used[i]) continue;
		assert(!used[i + 1]);
		ans.push_back({i, i + 1});
		used[i] = true;
		used[i + 1] = true;	
	}

	for (int i = 0; i < MAXN * 2; i++) {
		used[i] = false;
	}

	for (auto i : ans) {
		assert(used[i.first] == false);
		assert(used[i.second] == false);
		used[i.first] = true;
		used[i.second] = true;
	}
	assert(ans.size() == n);
	sort(all(ans));
	cout << "Yes" << "\n";
	for (auto i : ans)
		cout << i.first << " " << i.second << "\n";
	return 0;
}
















