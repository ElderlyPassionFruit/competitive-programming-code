#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get(int m, int d) {
	m--;
	d--;
	int ans = d;
	for (int i = 0; i < m; i++)
		ans += month[i];
	return ans;
}

int n;
vector<int> have;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int m, d;
		char x;
		cin >> m >> x >> d;
		int Have = get(m, d);

		for (int j = -5; j < 5; j++) {
			have.push_back(Have + j * 365);
		}
	}
	sort(all(have));
}

pair<int, int> get(int x) {
	int m = 0;
	int d = 0;
	for (int i = 0; i < month.size(); i++) {
		if (x - month[i] < 0) break;
		x -= month[i];
		m++;
	}
	m++;
	d = x + 1;
	return {m, d};
}

int get_dist(int pos) {
	int ans = 1e9;
	for (auto i : have) {
		if (i == pos) return -1e9;
		if (i > pos) break;
		chkmin(ans, pos - i);
	}
	return ans;
}

pair<int, int> fans;

void run() {
	sort(all(have));
	pair<int, int> ans = {0, 0};
	for (int j = 300; j < 300 + 365; j++) {
		int i = j % 365;
		if (get_dist(i) > ans.first) {
			ans = {get_dist(i), i};
		}
	}
	fans = get(ans.second);
}

void wr_int(int x) {
	if (x < 10)
		cout << "0" << x;
	else
		cout << x;
}

void write() {
	wr_int(fans.first);
	cout << "-";
	wr_int(fans.second);
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