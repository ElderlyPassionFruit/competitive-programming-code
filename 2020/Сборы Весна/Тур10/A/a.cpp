#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int cnt = 0;
int flag = 1;
pair<int, int> ans = {0, 0};
const int MAXN = 2e5 + 10;

int pref[MAXN][4];

void build() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 3; j++) {
			pref[i][j] = pref[i - 1][j];
		}
		if (a[i - 1] == -2) {
			pref[i][0]++;
		} else if (a[i - 1] == -1) {
			pref[i][1]++; 
		} else if (a[i - 1] == 1) {
			pref[i][2]++;
		} else if (a[i - 1] == 2) {
			pref[i][3]++;
		}
	}
}

void relax(int l, int r) {
	if (l > r) return;
	//cout << l << " " << r << endl;
	l++;
	r++;
	int cnt2 = pref[r][3] - pref[l - 1][3] + pref[r][0] - pref[l - 1][0];
	int cnt_minus = pref[r][1] - pref[l - 1][1] + pref[r][0] - pref[l - 1][0];
	cnt_minus %= 2;
	l--;
	r--;
	if (flag != cnt_minus && cnt_minus == 1) return;
	if (flag != cnt_minus) {
		flag = cnt_minus;
		cnt = cnt2;
		ans = {l, r};
		return;
	}
	if (cnt_minus == 0) {
		if (cnt < cnt2) {
			cnt = cnt2;
			ans = {l, r};
			return;
		}
	}
}

void solve(int l, int r) {
	if (l >= r) return;
	r--;
	relax(l, r);
	int pos = -1;
	for (int i = l; i <= r; i++) {
		if (a[i] < 0) {
			pos = i;
			break;
		}
	}
	if (pos == -1) return;
	relax(pos + 1, r);
	for (int i = r; i >= l; i--) {
		if (a[i] < 0) {
			pos = i;
			break;
		}
	}
	relax(l, pos - 1);
}

void run() {
	build();
	int pos = max_element(all(a)) - a.begin();
	//cout << "pos = " << pos << endl;
	if (abs(a[pos]) == 2) {
		cnt = 1;
	} else {
		cnt = 0;
	}
	if (a[pos] < 0) {
		flag = 1;
	} else {
		flag = 0;
	}
	ans = {pos, pos};
	int last = 0;
	a.push_back(0);
	for (int i = 0; i <= n; i++) {
		if (a[i] == 0) {
			solve(last, i);
			last = i + 1;
		}
	}
}

void write() {
	cout << ans.first + 1 << " " << ans.second + 1 << endl;
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