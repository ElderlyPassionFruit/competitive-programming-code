#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string s = "A23456789DQJK";

int getInd(char x) {
	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == x) {
			return i;
		}
	}
	assert(false);
	return -1;
}

const int MAXN = 13;

int n;
int pos;
bool ok;
int now;
string a[MAXN];

void check() {
	for (int i = 0; i < n; i++) {
		if (pos == i) continue;
		if ((int)a[i].size() != 4) continue;
		if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][2] == a[i][3]) {
			cout << i + 1 << endl;
			exit(0);
		}
	}
}

int cnt[MAXN];

void nxt() {
	if (pos == now && ok) {
		ok = false;
		pos++;
		if (pos == n) pos = 0;
	} else {
		if (!ok) ok = true;
		fill(cnt, cnt + MAXN, 0);
		for (auto i : a[now]) {
			cnt[getInd(i)]++;
		}
		int mn = 1e9;
		char fans = 'a';
		for (int i = 0; i < MAXN; i++) {
			if (!cnt[i]) continue;
			if (mn > cnt[i]) {
				mn = cnt[i];
				fans = s[i];
			}
		}
		assert(mn <= MAXN * 4);
		for (int i = 0; i < (int)a[now].size(); i++) {
			if (a[now][i] == fans) {
				a[now].erase(a[now].begin() + i);
				break;
			}
		}
		a[(now + 1) % n] += fans;
	}
	now++;
	if (now == n) now = 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> now;
	now--;
	pos = now;
	ok = false;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	while (true) {
		check();
		nxt();
	}
	return 0;
}