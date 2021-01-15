#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

const int MOD = 998244353;
const int p1 = 67, p2 = 47;
const int p = 67 * 47;
const int MAXN = 1e5 + 10;

int pows1[MAXN], pows2[MAXN];

int dx;

const int MAXL = 52;
const int MAXM = 1010;

int Hash[MAXL * 2][MAXM];

vector<int> fans;
map <int, int> ans;

int n, m, k, l;

int add(int x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}

int sub(int x, int y) {
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}

int mul(int x, int y) {
	long long ans = (long long)x * y;
	if (ans > MOD)
		ans %= MOD;
	return ans;
}

void build_pows() {
	pows1[0] = pows2[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows1[i] = mul(pows1[i - 1], p1);
		pows2[i] = mul(pows2[i - 1], p2);
	}
}

string table[MAXL];

int get_Hash() {
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			Hash[i][j] = 0;
			Hash[i][j] = add(Hash[i][j], mul(Hash[i - 1][j], p1));
			Hash[i][j] = add(Hash[i][j], mul(Hash[i][j - 1], p2));
			Hash[i][j] = sub(Hash[i][j], mul(Hash[i - 1][j - 1], p));
			Hash[i][j] = add(Hash[i][j], table[i - 1][j - 1] - '0' + 1);
		}
	}
	return Hash[l][l];
}

void read() {
	cin >> n >> m >> k >> l;
	build_pows();
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < l; j++)
			cin >> table[j];
		fans.push_back(get_Hash());
		ans[fans.back()] = 0;
	}
}

int get_Hash(int x1, int y1, int x2, int y2) {
	return sub(add(Hash[x2 - dx][y2], mul(Hash[x1 - 1 - dx][y1 - 1], mul(pows1[l], pows2[l]))), add(mul(Hash[x1 - 1 - dx][y2], pows1[l]), mul(Hash[x2 - dx][y1 - 1], pows2[l])));
}

void build_hash() {
	dx = 0;
	for (int i = 1; i <= n; i++) {
		if (i - dx > 2 * l) {
			for (int j = 1; j <= l; j++) {
				for (int k = 1; k <= m; k++) {
					Hash[j][k] = Hash[j + l][k];
				}
			}
			dx += l;
		}

		string s;
		cin >> s;
		for (int j = 1; j <= m; j++) {
			char c;
			c = s[j - 1];
			int x = i - dx;
			Hash[x][j] = 0;
			Hash[x][j] = add(Hash[x][j], mul(Hash[x - 1][j], p1));
			Hash[x][j] = add(Hash[x][j], mul(Hash[x][j - 1], p2));
			Hash[x][j] = sub(Hash[x][j], mul(Hash[x - 1][j - 1], p));
			Hash[x][j] = add(Hash[x][j], (c - '0' + 1));
			if (i - l + 1 >= 1 && j - l + 1 >= 1) {
				int fans = get_Hash(i - l + 1, j - l + 1, i, j);
				if (ans.find(fans) != ans.end())
					ans[fans]++;
			}
		}
	}
}

void run() {
	build_hash();
}

void write() {
	for (int i = 0; i < k; i++)
		cout << i + 1 << " " << ans[fans[i]] << "\n";
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