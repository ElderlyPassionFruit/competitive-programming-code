#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
struct segment{
	int l, r, ind;
	segment() {}
};

int n;
vector<segment> a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].l >> a[i].r;
		a[i].r -= 5;
		a[i].ind = i;
	}
	vector<segment> help;
	for (auto i : a) {
		if (i.l <= i.r)
			help.push_back(i);
	}
	a = help;
	n = a.size();
	for (int i = 0; i < n; i++) {
		a[i].ind = i;
	}
}
vector<int> have;

int ans;
int f, s;

void make() {
	for (auto &i : a) {
		have.push_back(i.l);
		have.push_back(i.r);
	}
	have.push_back(1);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	//for (auto &i : a) {
	//	i.l = lower_bound(all(have), i.l) - have.begin();
	//	i.r = lower_bound(all(have), i.r) - have.begin();
	//}
	have.push_back(2e9);
}

int calc(int pos1, int pos2) {
	if (abs(have[pos1] - have[pos2]) < 5) return -1;
	int ans = 0;
	for (auto i : a) {
		if (i.l <= have[pos1] && i.r >= have[pos1]) ans++;
		else if (i.l <= have[pos2] && i.r >= have[pos2]) ans++;
	}
	return ans;
}

void run() {
	make();
	ans = -1;
	for (int i = 0; i < have.size(); i++) {
		for (int j = i + 1; j < have.size(); j++) {
			int fans = calc(i, j);
			if (ans < fans) {
				ans = fans;
				f = i;
				s = j;
			}
		}
	}
}

void write() {
	//assert(f != s);
	f = have[f];
	s = have[s];
	//assert(f <= s - 5);
	cout << ans << " " << f << " " << s << endl;
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