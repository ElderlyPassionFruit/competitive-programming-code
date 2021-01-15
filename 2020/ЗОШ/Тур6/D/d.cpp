#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string s;

void read() {
	cin >> n >> s;
	s = s + s;
}

const int MAXN = 2e5 + 10;
int pref[MAXN][3];
int cnt[3];

void build() {
	for (int i = 1; i <= 2 * n; i++) {
		for (int j = 0; j < 3; j++) 
			pref[i][j] = pref[i - 1][j];
		cnt[s[i - 1] - 'A']++;
		pref[i][s[i - 1] - 'A']++;
	}
	for (int i = 0; i < 3; i++)
		cnt[i] /= 2ж
}

int get(int l, int r, int id) {
	if (l > r) return 0;
	return pref[r][id] - pref[l - 1][id];
}

int calc(int pos, int s1, int s2, int s3) {
	int ans = 0;
	ans += get(pos, pos + cnt[s1] - 1, s1);
	pos += cnt[s1];
	ans += get(pos, pos + cnt[s2] - 1, s2);
	pos += cnt[s2];
	ans += get(pos, pos + cnt[s3] - 1, s3);
	return n - ans;
}

int calc(int pos) {
	vector<int> have = {0, 1, 2};
	int ans = n;
	do {
		chkmin(ans, calc(pos, have[0], have[1], have[2]));
	} while (next_permutation(all(have)));
	return ans;
}

int ans;

void run() {
	build();
	ans = n;
	calc(0);
	for (int i = 1; i <= n; i++) {
		chkmin(ans, calc(i));
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