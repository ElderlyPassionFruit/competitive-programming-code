#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int n = 128;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int Q = 850;
char ans[n];

string my;
int base;
vector<char> have;

int query(string s) {
	Q--;
	assert(Q >= 0);
	cout << "? " << s << endl;
	int ans;
	cin >> ans;
	return ans;
}

set<int> pos;

void gen() {
	for (int i = 0; i < 26; i++) {
		have.push_back('a' + i);
		have.push_back('A' + i);
		if (i < 10) have.push_back('0' + i);
	}
	for (int i = 0; i < n; i++) {
		pos.insert(i);
		my += have[rnd() % (int)have.size()];
	}
	base = query(my);
}

string gen(int len, char x) {
	string ans = "";
	for (int i = 0; i < len; i++) {
		ans += x;
	}
	for (int i = len; i < n; i++) {
		ans += my[i];
	}
	return ans;
}

int find_nxt(char x, int l) {
	int now = query(gen(l + 1, x));
	int r = n - 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (query(gen(mid + 1, x)) >= now) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return r;
}

void solve(char x) {
	if (pos.empty()) return;
	string fcnt = gen(n, x);
	int cnt = query(fcnt);
	int l = -1;	
	while (cnt > 0) {
		l = find_nxt(x, l);
		ans[l] = x;
		cnt--;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	gen();
	shuffle(all(have), rnd);
	for (auto i : have) {
		solve(i);
	}
	cout << "! ";
	for (int i = 0; i < n; i++) {
		cout << ans[i];
	}
	cout << endl;
	return 0;
}