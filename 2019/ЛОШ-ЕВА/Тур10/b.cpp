#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
string s;
int n;
void read() {
	cin >> s;
	n = s.size();
}
int ans;
void run() {
	int fans = 0;
	ans = n * (n - 1) / 2;
	char last = s[0];
	int pos = 0;
	vector<pair<int, char> > bloks;
	for (int i = 1; i < n; i++) {
		if (s[i] != last) {
			int len = min(i - pos, 2LL);
			bloks.pb({len, last});
			last = s[i];
			pos = i;
		}
	}

	int len = min(n - pos, 2LL);
	bloks.pb({len, last});

	if (bloks.size() == 1) {
		ans = 1;
		return;
	}

	int sz_last = bloks[1].first;
	char pre_last = bloks[1].second;
	last = bloks[0].second;
	ans = 0;

	int sum_sz = bloks[0].first + bloks[1].first - 1;
	ans = sum_sz;

	for (int i = 2; i < bloks.size(); i++) {
		if (sz_last == 1 && bloks[i].second == last) {
			ans += bloks[i].first + i - 2; 
		}
		else {
			ans += bloks[i].first + i - 1;
		}
		sz_last = bloks[i].first;
		last = pre_last;
		pre_last = bloks[i].second;
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}