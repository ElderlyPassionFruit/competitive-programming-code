#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
int a[MAXN], p[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int ans;

void build() {
	for (int i = 0; i < MAXN; i++)
		p[i] = 0;
	for (int i = 0; i < n; i++)
		p[a[i]]++;
	for (int i = 1; i < MAXN; i++)
		p[i] += p[i - 1];
}

int get(int l, int r) {
	return p[min(r, MAXN - 1)] - (l > 0 ? p[l - 1] : 0);
}

int calc(int x) {
	if (!get(x, x)) return 0;
	int ans = 0;
	for (int i = x; i < MAXN; i += x) {
		ans += get(i, i + x - 1) * i;
		//cout << i << " " << i + x - 1 << " " << get(i, i + x - 1) << endl;
	}
	return ans;
}

void run() {
	build();

	ans = 0;
	//cout << calc(3) << endl; 
	for (int i = 1; i < MAXN - 1; i++) {
		chkmax(ans, calc(i));
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