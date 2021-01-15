#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e5 + 10;
int n, l;
ll a[MAXN];
vector<ll> coord;

void read() {
	cin >> n >> l;
	coord.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i] = a[i] * l + i;
		coord[i] = a[i];
	}
}

int tree[MAXN];

void upd(int pos) {
	for (; pos < n; pos |= pos + 1)
		tree[pos]++;
}

int fget(int r) {
	int ans = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		ans += tree[r];
	return ans;
}

int get(int r) {
	return fget(n - 1) - fget(r - 1);
}

ll ans;

void run() {
	sort(all(coord));
	coord.resize(unique(all(coord)) - coord.begin());
	ans = 0;
	/*cout << "a = " << endl;
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl; */
	for (int i = 0; i < n; i++) {
		int pos = upper_bound(all(coord), a[i]) - coord.begin();
		ans += get(pos);
		upd(pos - 1);
	}	
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