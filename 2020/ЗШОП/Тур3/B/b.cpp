#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
string s;
const int MAXN = 2e5 + 10;

void read() {
	cin >> n >> k;
	cin >> s;
}

struct segment{
	int l, r;
	segment() {}
	segment(int _l, int _r) {
		l = _l, r = _r;
	}
};

vector<segment> have[3];

void build(int ind, char x) {
	int r, cnt;
	r = cnt = 0;
	for (int l = 0; l < n; l++) {
		if (s[l] != x) continue;
		chkmax(r, l);
		while (r < n && cnt < k) {
			if (s[r] == x) cnt++;
			r++;
		}
		if (cnt == k)
			have[ind].push_back({l, r - 1});
		cnt--;
	}
}

int L[MAXN], R[MAXN];

void build() {
	build(0, 'J');
	build(1, 'O');
	build(2, 'I');
	for (int i = 0; i < MAXN; i++) L[i] = -1, R[i] = n;
	for (auto i : have[0])
		chkmax(L[i.r], i.l);
	for (auto i : have[2])
		chkmin(R[i.l], i.r);
	for (int i = 1; i < n; i++)
		chkmax(L[i], L[i - 1]);
	for (int i = n - 2; i >= 0; i--)
		chkmin(R[i], R[i + 1]);
}

const int INF = 1e9;

int ans;

void calc() {
	ans = INF;
	for (auto i : have[1]) {
		if (i.l == 0) continue;
		if (i.r == n - 1) continue;
		if (L[i.l - 1] == -1) continue;
		if (R[i.r + 1] == n) continue;
		int fans = R[i.r + 1] - L[i.l - 1] + 1;
		fans -= 3 * k;
		chkmin(ans, fans);
	}
}

void run() {
	build();
	calc();
}

void write() {
	if (ans == INF) ans = -1;
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