#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 110;
int n, a;
int t[MAXN];
int sum, mn, mx;

void check(vector<int> ans) {
	reverse(all(ans));
	for (int i = n - 1; i >= 0; i--) {
		ans.push_back(t[i]);
	}
	reverse(all(ans));
	for (int i = n; i < (int)ans.size(); i++) {
		int mn = *min_element(ans.begin() + i - n, ans.begin() + i);
		int mx = *max_element(ans.begin() + i - n, ans.begin() + i);
		assert(ans[i] >= mn && ans[i] <= mx);
	}
	sum = 0;
	for (auto i : ans) {
		sum += i;
	}
	sum /= (int)ans.size();
	assert(sum == a);
}

void solve(int m) {
	int l = a * (n + m);
	int r = l + n + m - 1;
	int canL = sum + mn * m, canR = sum + mx * m;
	//cout << "l = " << l << " r = " << r << " canL = " << canL << " canR = " << canR << endl;
	if (canL > r || canR < l) return;
	int my_sum = min(r, canR) - sum;
	int cnt1 = my_sum % m;
	int cnt0 = m - cnt1;
	int val = my_sum / m;
	//cout << "my_sum = " << my_sum << endl;
	vector<int> ans;
	int my_mn = *min_element(t + 1, t + n);
	int my_mx = *max_element(t + 1, t + n);
	if (my_mx < (cnt1 > 0) + val) {
		if (cnt1 > 0) {
			ans.push_back(val + 1);
			cnt1--;
		} else {
			ans.push_back(val);
			cnt0--;
		}
	} else if (my_mn > val) {
		ans.push_back(val);
		cnt0--;
	} else {
		if (cnt1 > 0) {
			ans.push_back(val + 1);
			cnt1--;
		} else {
			ans.push_back(val);
			cnt0--;
		}
	}
	for (int i = 0; i < m - 1; i++) {
		if (ans.back() == val && cnt1) {
			ans.push_back(val + 1);
			cnt1--;
		} else if (ans.back() == val + 1 && cnt0) {
			ans.push_back(val);
			cnt0--;
		} else if (cnt1) {
			ans.push_back(val + 1);
			cnt1--;
		} else {
			assert(cnt0);
			ans.push_back(val);
			cnt0--;
		}
	}
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
	check(ans);
	assert(cnt0 == 0 && cnt1 == 0);
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> a;
	sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> t[i];
		sum += t[i];
	}
	mn = *min_element(t, t + n);
	mx = *max_element(t, t + n);
	//cout << sum << " " << mn << " " << mx << endl;
	for (int i = 1; i <= 1e7; i++) {
		solve(i);
	}
	cout << -1 << endl;
	return 0;
}

/*
7 3
1 9 3 10 8 9 6 


*/