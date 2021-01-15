#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int a, b, c;
	event() {}
	event(int x, int y, int z) {
		a = x, b = y, c = z;
	}
};

int n, s;
vector<event> a;

void read() {
	cin >> n >> s;
	a.resize(n);
	for (auto &i : a)
		cin >> i.a >> i.b >> i.c;
}

bool check(int cnt) {
	vector<int> have;
	for (auto i : a) {
		if (i.c >= cnt)
			have.push_back(i.a);
		else
			have.push_back(i.b);
	}
	sort(all(have));
	int can = s;
	for (int i = 0; i < cnt; i++) {
		can -= have[i];
	}
	return can >= 0;
}

int ans;

void run() {
	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
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