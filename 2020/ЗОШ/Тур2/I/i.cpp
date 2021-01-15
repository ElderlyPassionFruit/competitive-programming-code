#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e4 + 10;

int used[MAXN];
int c = 0;

int h, w;
int n;

struct rect{
	int x1, y1, x2, y2;
	rect() {}
};

vector<rect> a;

void read() {
	cin >> h >> w;
	cin >> n;
	for (int i = 0; i < n; i++) {
		rect b;
		cin >> b.x1 >> b.y2 >> b.x2 >> b.y1;
		a.push_back(b);
		used[i] = c++;
	}
}

bool check(int x, int y, int ind) {
	return a[ind].x1 <= x && x <= a[ind].x2 && a[ind].y1 <= y && y <= a[ind].y2;
}

void run() {
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		int ans = -1;
		for (int j = 0; j < n; j++) {
			if (check(x, y, j)) {
				if (ans == -1)
					ans = j;
				else if (used[ans] < used[j]) {
					ans = j;
				}
			}
		}	
		if (ans == -1) {
			cout << 0 << "\n";
		}
		else {
			used[ans] = c++;
			cout << ans + 1 << "\n";
		}
	}
}

void write() {

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