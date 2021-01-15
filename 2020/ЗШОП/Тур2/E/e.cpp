#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string a;
string b;

void read() {
	cin >> a >> b;
}

int ans;

const int MAXN = 30;
int g[MAXN];

bool check(char x, char y) {
	vector<char> haveA, haveB;
	for (auto i : a) if (i == x || i == y) haveA.push_back(i);
	for (auto i : b) if (i == x || i == y) haveB.push_back(i);
	return haveA == haveB;
}

int sz;

void wr(int mask) {
	while (mask) {
		cout << mask % 2 << " ";
		mask /= 2;
	}
	cout << endl;
}

void build() {
	ans = 0;
	map<char, int> cntA, cntB;
	set<char> have;
	
	for (auto i : a) cntA[i]++, have.insert(i);
	for (auto i : b) cntB[i]++, have.insert(i);
	sz = have.size();
	map<char, bool> used;
	for (char i = 'a'; i <= 'z'; i++) used[i] = cntA[i] != cntB[i], ans += used[i];
	sz -= ans;
	if (sz == 0) {
		cout << ans << endl;
		exit(0);
	}
	for (int i = 'a'; i <= 'z'; i++) {
		for (int j = i; j <= 'z'; j++) {
			if (!have.count(i)) continue;
			if (!have.count(j)) continue;
			if (used[i]) continue;
			if (used[j]) continue;
			if (i == j) {
				g[i - 'a'] |= (1 << (j - 'a'));
				g[j - 'a'] |= (1 << (i - 'a'));
				continue;
			}
			if (!check(i, j)) continue;
			g[i - 'a'] |= (1 << (j - 'a'));
			g[j - 'a'] |= (1 << (i - 'a'));
		}
	}
}

const int MAXA = 13;

bool check(int mask, int pos) {
	int fans = (1 << MAXA) - 1;
	for (int i = 0; i < MAXA; i++) {
		if ((mask >> i) & 1) {
			fans &= (g[i + pos] >> pos);
		}
	}
	return mask == (mask & fans);
}

int get(int mask) {
	int ans = 0;
	while (mask) {
		ans += mask % 2;
		mask /= 2;
	}
	return ans;
}

int dp[1 << MAXA];

void calc() {
	int fans = 0;
	for (int mask = 1; mask < (1 << MAXA); mask++) {
		dp[mask] = check(mask, 0) * get(mask); 
		for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
			chkmax(dp[mask], dp[submask]);
		}
		chkmax(fans, dp[mask]);
	}
	for (int mask = 1; mask < (1 << MAXA); mask++) {
		if (!check(mask, MAXA)) continue;
		int fmask = (1 << MAXA) - 1;
		for (int i = 0; i < MAXA; i++) {
			if ((mask >> i) & 1) {
				fmask &= g[i + MAXA];
			}
		}
		chkmax(fans, get(mask) + dp[fmask]);
	}
	ans += sz - fans;
}

void run() {
	build();
	calc();
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