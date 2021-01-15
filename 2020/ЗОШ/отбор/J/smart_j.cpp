#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};
#define int ll
struct point{
	int x, y, posx, posy;
	point() {}
	point(int a, int b) {
		x = a, y = b;
	}
};

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

int n;
vector<point> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto &i : a)
    	cin >> i.x >> i.y;
}

ll ans;
int xl;

const ll INF = 1e18;

ll solve() {
	vector<pair<int, int> > x, y;
	vector<bool> ux, uy;
	int cnt = 0;
	for (auto i : a) {
		x.push_back({i.x, cnt});
		y.push_back({i.y, cnt});
		cnt++;
	}
	assert(cnt == n);
	sort(all(x));
	sort(all(y));
	for (int i = 0; i < n; i++) {
		a[x[i].second].posx = i;
		a[y[i].second].posy = i;
	}
	ux.resize(n, false);
	uy.resize(n, false);

	ll ans = INF;
	int xl = x[0].first;
	int yl = y[0].first;
	int xr = xl;
	int yr = yl;

	int posxL = 0, posxR = n - 1, posyL = 0, posyR = n - 1;

	for (int i = 0; i < n; i++) {
		chkmax(xr, a[i].x);
		chkmax(yr, a[i].y);
		ux[a[i].posx] = true;
		uy[a[i].posy] = true;
		while (posxL < posxR && ux[posxL]) posxL++;
		while (posxL < posxR && ux[posxR]) posxR--;
		while (posyL < posyR && uy[posyL]) posyL++;
		while (posyL < posyR && uy[posyR]) posyR--;
		ll d = max(x[posxR].first - x[posxL].first, y[posyR].first - y[posyL].first);
		ll fans = max(xr - xl, yr - yl);
		ans = min(ans, d * d + fans * fans);
	}
	return ans;
}

void run() {
	ans = INF;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			ll xl = INF, yl = INF;
			for (auto k : a) {
				chkmin(xl, k.x);
				chkmin(yl, k.y);
			}
			//reverse(all(a));
			sort(all(a), [&] (point & i, point & j) {return max(i.x - xl, i.y - yl) < max(j.x - xl, j.y - yl);});
			chkmin(ans, solve());
			for (auto &k : a)
				k.x *= -1;
		}
		for (auto &k : a)
			k.y *= -1;
	}
}

void write() {
	cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
    	read();
    	run();
    	write();
	}
    return 0;
}