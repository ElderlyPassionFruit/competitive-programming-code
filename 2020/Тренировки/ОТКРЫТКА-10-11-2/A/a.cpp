#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int id, reg, score, flag;
	event() {}
};

int n, m, r;
vector<event> have;

void read() {
	cin >> n >> m >> r;
	have.resize(n);
	for (auto &i : have) {
		cin >> i.id >> i.reg >> i.score >> i.flag;
	}
}

const int MAXN = 1e5 + 10;

bool used[MAXN];

bool check(int val) {
	for (int i = 1; i <= r; i++)
		used[i] = false;
	int fans = 0;
	for (auto i : have) {
		if (i.flag || i.score >= val) {
			fans++;
			used[i.reg] = true;
		}
	}
	for (auto i : have) {
		if (i.flag || i.score >= val) continue;
		if (used[i.reg]) continue;
		fans++;
		used[i.reg] = true;
	}
	return fans <= m;
}

int ans;

void run() {
	int l = -1, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) 
			r = mid;
		else
			l = mid;
	}
	ans = r;
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