#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;
int b = rand() % 1000 + 228;

const int MAXN = 1e5 + 10;
int pows[MAXN];

int add(int a, int b, int MOD) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b, int MOD) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b, int MOD) {
	return (ll) a * b % MOD;
}

void build() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = mul(pows[i - 1], b, MOD);
	}
}

int hashs[2][MAXN];
int rhash[2][MAXN];

int n;
string s[2];

void read() {
	cin >> n;
	cin >> s[0] >> s[1];
}

void build_hash() {
	hashs[0][0] = hashs[1][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2; j++) {
			hashs[j][i] = add(mul(hashs[j][i - 1], b, MOD), s[j][i - 1], MOD);
		}
	}
	rhash[0][n + 1] = rhash[1][n + 1] = 0;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 2; j++) {
			rhash[j][i] = add(mul(rhash[j][i + 1], b, MOD), s[j][i - 1], MOD);
		}
	}
}

int get_hashs(int l, int r, int id) {
	l++;
	r++;
	return sub(hashs[id][r], mul(hashs[id][l - 1], pows[r - l + 1], MOD), MOD);
}

int get_rhash(int l, int r, int id) {
	l++;
	r++;
	return sub(rhash[id][l], mul(rhash[id][r + 1], pows[r - l + 1], MOD), MOD);
}

int Get_hashs(int i, int j, int k) {
	if (i == -1) {
		return get_hashs(j, k, 1);
	}
	if (k == -1) {
		return get_hashs(i, j, 0);
	}
	return add(mul(get_hashs(i, j, 0), pows[k - j + 1], MOD), get_hashs(j, k, 1), MOD);
}

int Get_rhash(int i, int j, int k) {
	if (i == -1) {
		return get_rhash(j, k, 1);
	}
	if (k == -1) {
		return get_rhash(i, j, 0);
	}
	return add(get_rhash(i, j, 0), mul(get_rhash(j, k, 1), pows[j - i + 1], MOD), MOD);
}

bool check(int x) {
	return x >= 0 && x < n;
}

bool check(int i, int j, int k) {
	return Get_hashs(i, j, k) == Get_rhash(i, j, k);
}

struct Fans{
	int i, j, k;
	Fans() {}
	Fans(int a, int b, int c) {
		i = a, j = b, k = c;
	}
};

int get_len(Fans a) {
	if (a.i == -1 && a.j == -1 && a.k == -1) return 0;
	if (a.i == -1) return a.k - a.j + 1;
	if (a.k == -1) return a.j - a.i + 1;
	return a.k - a.i + 2; 
}

bool operator<(const Fans & a, const Fans & b) {
	return get_len(a) < get_len(b);
}

Fans fans;

string ans[2];

void make_ans() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			ans[j] += ".";
		}
	}
	if (fans.j == -1) return;
	

	if (fans.i != -1) assert(fans.i <= fans.j);
	if (fans.k != -1) assert(fans.j <= fans.k);
	if (fans.i != -1)
	for (int i = fans.i; i <= fans.j; i++)
		ans[0][i] = s[0][i];
	
	if (fans.k != -1)
	for (int i = fans.j; i <= fans.k; i++)
		ans[1][i] = s[1][i];
}

void run() {
	build_hash();
	fans = {-1, -1, -1};
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (check(i, j, -1)) {
				chkmax(fans, Fans(i, j, -1));
			}
			if (check(-1, i, j)) {
				chkmax(fans, Fans(-1, i, j));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			for (int k = j; k < n; k++) {
				if (check(i, j, k)) {
					chkmax(fans, Fans(i, j, k));
				}
			}
		}
	}

	make_ans();
}

void write() {
	cout << get_len(fans) << endl;
	cout << ans[0] << endl;
	cout << ans[1] << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	read();
	run();
	write();
	return 0;
}