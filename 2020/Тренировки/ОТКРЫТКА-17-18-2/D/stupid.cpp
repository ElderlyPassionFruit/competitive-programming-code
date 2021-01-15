#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

const int MAXN = 5e5 + 10;
const int MAXA = 26;

mt19937 rnd(time(0));

vector<int> MOD = {998244353, 1000000007};
vector<int> base = {rnd() % 1000 + 228 + 1337, rnd() % 1000 + 228 + 1337};

int add(int a, int b, int ind) {
	a += b;
	if (a >= MOD[ind]) 
		a -= MOD[ind];
	return a;
}

int sub(int a, int b, int ind) {
	a -= b;
	if (a < 0) 
		a += MOD[ind];
	return a;
}

int mul(int a, int b, int ind) {
	return (ll) a * b % MOD[ind];
}

int pows[2][MAXA];
int h[2][MAXN];

void build() {
	pows[0][0] = pows[1][0] = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= MAXA; j++) {
			pows[i][j] = mul(pows[i][j - 1], base[i], MOD[i]);
		}
	}
	h[0][0] = h[1][0] = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= n; j++) {
			h[i][j] = add(h[i][j - 1], pows[i][s[j - 1] - 'a'], MOD[i])
		}
	}
}

int get(int l, int r, int type) {
	return sub(h[type][r], h[type][l - 1], MOD[type]);
}

pair<int, int> get(int l, int r, int type) {
	return {get(l, r, 0), get(l, r, 1)};
}

bool check(int len) {
	for (int i = len + 1; i <= n; i += len) {
		if (get(1, len) != get(i, i + len - 1)) {
			//cout << "i = " << i << " j = " << j << endl;
			return false;
		}
	}
	return true;
}

int ans;

void run() {
	build();
	ans = 1;
	//cout << check(3) << endl;
	//return;
	for (int len = 1; len * len <= n; len++) {
		if (n % len) continue;
		if (n / len > ans && check(len)) ans = n / len;
		if (len > ans && check(n / len)) ans = len; 
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