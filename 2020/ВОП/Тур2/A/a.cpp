#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;
ll full;

void read() {
	cin >> n >> k;
	a.resize(n + k);
	for (auto &i : a) {
		cin >> i;
	}
	sort(all(a));
	full = 0;
	for (auto i : a)
		full += i;
}

mt19937 rnd(time(0));

void solve(int start, int pos) {
	vector<int> ans;
	int sum = a[start] + a[pos];
	ans.push_back(a[start]);
	ans.push_back(a[pos]);
	int cnt = start + n + k - 1 - pos;
	pos--;
	for (int i = start + 1; i < pos && (int)ans.size() < n && cnt <= k; i++) {
		while (pos - 1 > i && a[i] + a[pos] > sum) pos--, cnt++;
		while (pos + 1 < n + k && a[i] + a[pos] < sum) pos++, cnt--;
		if (i < pos && a[i] + a[pos] == sum) {
			ans.push_back(a[i]);
			ans.push_back(a[pos]);
			pos--;
		}
	}
	while (ans.size() > n) ans.pop_back();
	if (ans.size() == n) {
		sort(all(ans));
		for (auto i : ans) {
			cout << i << " ";
		}
		cout << endl;
		exit(0);
	}
}

void run() {
	for (int start = 0; start <= k; start++) {
		for (int i = 0; i + start <= k; i++) {
			solve(start, n + k - 1 - i);
		}
	}
}

void write() {
	//assert(false);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}