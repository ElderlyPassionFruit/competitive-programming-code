#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<int> d, a;

void read() {
	cin >> n >> m;
	d.resize(n);
	for (auto &i : d)
		cin >> i;
	a.resize(m);
	for (auto &i : a)
		cin >> i;
	/*cout << n << " " << m << endl;
	for (auto i : d)
		cout << i << " ";
	cout << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;*/
}

bool check(int day) {
	vector<int> last(m, -1);
	vector<int> days(n, -1);

	for (int i = day - 1; i >= 0; i--) {
		if (d[i] == 0)
			continue;
		if (last[d[i] - 1] == -1) {
			last[d[i] - 1] = i;
			days[i] = d[i] - 1;
		}
	}
	vector<pair <int, int> > need;
	for (int i = 0; i < m; i++)
		need.push_back({last[i], a[i]});
	sort(need.begin(), need.end());
	/*cout << "days = " << endl;
	for (auto i : days)
		cout << i << " ";
	cout << endl;
	cout << "last = " << endl;
	for (auto i : last)
		cout << i << " ";
	cout << endl;
	cout << "need = " << endl;
	for (auto i : need)
		cout << i.first << " " << i.second << endl;
	*/
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (pos < m && need[pos].second > 0 && need[pos].first <= i)
			return false;
		if (days[i] != -1)
			continue;
		while (pos < m && need[pos].second == 0)
			pos++;
		if (pos < m)
			need[pos].second--;
	}
	return true;
}

int ans = -1;

void run() {
	if (!check(n))
		return;
	int l = 0, r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	ans = r;
	//cout << check(8) << endl;
}

void write() {
	cout << ans << endl;
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