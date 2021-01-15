#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

vector<int> zf(string s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = -1;
	for (int i = 1; i < n; i++) {
		if (r >= i)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]])
			z[i]++;
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

vector<int> cnt;

void build() {
	auto z = zf(s);
	cnt.resize(n);
	vector<int> del(n);
	int add = 0;
	for (int i = 1; i < n; i++) {
		cnt[i] += add;
		if (z[i] == 0) {
			add += del[i];
			continue;
		}
		add++;
		cnt[i]++;
		del[i + z[i] - 1]--;
		add += del[i];
	}

	/*for (auto i : s)
		cout << i << " ";
	cout << endl;
	for (auto i : z)
		cout << i << " ";
	cout << endl;
	for (auto i : cnt)
		cout << i << " ";
	cout << endl;*/
}

string ans;

void run() {
	build();
	int pos_ans = 0;
	int mx = 0;
	for (int i = 0; i < n; i++) {
		if (cnt[i] > mx)
			pos_ans = i;
		chkmax(mx, cnt[i]);
	}
	ans = "";
	for (int i = 0; i <= pos_ans; i++)
		ans += s[i];
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}