#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


vector<pair <char, pair <int, int> > > a;
int n;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second.first >> i.second.second;
}

int ans;

int calc() {
	int ans = 0;
	int cnt_R = 0, cnt_B = 0;
	int have_R = 0, have_B = 0;
	for (auto i : a) {
		int need_R = max(i.second.first - cnt_R, 0LL);
		int need_B = max(i.second.second - cnt_B, 0LL);
		int fans = max(need_R - have_R, need_B - have_B);
		//cout << "fans = " << fans << endl;
		have_R += fans - need_R;
		have_B += fans - need_B;
		ans += fans;

		if (i.first == 'R')
			cnt_R++;
		else
			cnt_B++; 
	}
	cout << endl;
	return ans;
}

void run() {
	ans = 1e18;
	do {
		chkmin(ans, calc());
	} while (next_permutation(a.begin(), a.end()));
}

void write() {
	cout << ans + n << endl;
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