#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {
		x = 0, y = 0;
	}
	pt(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

int n;
vector<pt> a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++)
		cin >> a[i].x >> a[i].y;
	sort(all(a));
}

vector<pt> ans;

void solve(vector<pt> a) {
	int n = a.size();
	if (n <= 1) return;
	n /= 2;
	for (auto i : a) {
		ans.push_back(pt(a[n].x, i.y));
	}
	vector<pt> L, R;
	for (auto i : a) {
		if (L.size() < n)
			L.push_back(i);
		else
			R.push_back(i);
	}
	solve(L);
	solve(R);
}

void run() {
	solve(a);
}

void write() {
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	vector<pt> Ans;
	for (auto i : ans) {
		if (binary_search(all(a), i)) continue;
		Ans.push_back(i);
	}
	ans = Ans;
	assert(ans.size() <= 10000);
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i.x << " " << i.y << "\n";
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