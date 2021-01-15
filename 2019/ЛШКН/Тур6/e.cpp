#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct card{
	int p, c, l;
};

int n, k;
vector<card> a;
void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i.p >> i.c >> i.l;
}

vector<vector<int> > 

bool check(int level) {
	vector<card> odd;
	vector<card> even;
	for (auto i : a) {
		if (i.l <= level) {
			if (i.c)
		}
	}

}

int ans = -1;

void run() {
	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	if (check(r))
		ans = r;
	else
		ans = -1;
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