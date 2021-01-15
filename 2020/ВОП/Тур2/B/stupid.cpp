#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}


struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

int h, w, n;
vector<pt> a;

void read() {
	cin >> h >> w >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
}


void solve() {
	pt s, f;
	cin >> s.x >> s.y >> f.x >> f.y;
	if (s.x > f.x) {
		cout << "No\n";
		return;
	}
	if (s.x == f.x) {
		if (s.y <= f.y) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
		return;
	}
	queue<int> q;
	vector<bool> used(n, false);
	for (int i = 0; i < n; i++) {
		if (a[i].x == s.x && a[i].y >= s.y) {
			q.push(i);
			used[i] = true;
		}
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (a[v].x == f.x && a[v].y <= f.y) {
			cout << "Yes\n";
			return;
		}
		if (a[v].x == f.x - 1 && a[v].y <= f.y) {
			cout << "Yes\n";
			return;
		}
		for (int i = 0; i < n; i++) {
			if (used[i]) continue;
			if (a[i].x == a[v].x && a[i].y >= a[v].y) {
				q.push(i);
				used[i] = true;
				continue;
			}
			if (a[i].x == a[v].x + 1 && a[i].y >= a[v].y) {
				q.push(i);
				used[i] = true;
				continue;
			}
		}
	}
	cout << "No\n";
}

void run() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}