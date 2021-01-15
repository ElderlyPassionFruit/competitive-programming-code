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
	int x, y;
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

ll solve(int len) {
	multiset<int> x, y;
	for (auto i : a) {
		x.insert(i.x);
		y.insert(i.y);
	}
	ll ans = INF;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		while (pos < n && a[pos].y - a[i].y <= len) {
			if (a[pos].x <= len + xl) {
				x.erase(x.find(a[pos].x));
				y.erase(y.find(a[pos].y));
			}
			pos++;
		}
		if (x.empty()) {
			ans = 0;
		}
		else {
			ll dx = (*(--x.end())) - (*x.begin());
			ll dy = (*(--y.end())) - (*y.begin());
			ans = min(ans, max(dx, dy));
		}
		x.insert(a[i].x);
		y.insert(a[i].y);
	}
	return ans;
}


void run() {
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	assert(a.size() == n);
	vector<int> len;
	for (int i = 0; i < n; i++) {
		len.push_back(a[i].x - a[0].x);
	}
	xl = a[0].x;
	sort(all(a), [&] (point & i, point & j) {return tie(i.y, i.x) < tie(j.y, j.x);});
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			len.push_back(a[j].y - a[i].y);
		}
	}
	sort(all(len));
	len.resize(unique(all(len)) - len.begin());
	ans = INF;
	/*int l = 0, r = len.size();
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (mid - solve(len[mid]) <= 0)
			l = mid;
		else
			r = mid;
	}
	for (int i = max(0LL, l); i <= min((int)len.size() - 1, r); i++) {
		int x = solve(len[i]);
		ans = min(ans, x * x + len[i] * len[i]);
	}*/
	//int last = 0;
	for (int i = 0; i < len.size(); i++) {
		int x = solve(len[i]);
		ans = min(ans, x * x + len[i] * len[i]);
		
		//cout << x * x + len[i] * len[i] - last << " ";
		//last = x * x + len[i] * len[i];
	}
	//cout << endl;
}

void write() {
	cout << ans << endl;
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