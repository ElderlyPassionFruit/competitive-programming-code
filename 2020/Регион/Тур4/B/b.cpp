#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110, MAXLEN = 5;
#define int ll
map<string, ll> dp[MAXN];
string s;
int n;

void read() {
	cin >> s >> n;
}

ll ans;

string get(string s, int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++)
		ans += s[i];
	return ans;
}

bool check(string s, string t) {
	for (int i = 0; i + s.size() - 1 < t.size(); i++) {
		if (get(t, i, i + s.size() - 1) == s)
			return false;
	}
	return true;
}

bool check(string t) {
	string t1 = t;
	reverse(all(t1));
	return check(s, t) && check(s, t1);
}

int fn = 0;

bool check_ans(string t) {
	string fans = t;
	if (fn & 1) t.pop_back();
	reverse(all(t));
	fans += t;
	return check(s, fans);
}

void run() {
	for (int i = 0; i <= 1; i++) {
		string x = "";
		x += 'A' + i;
		if (x != s)
			dp[1][x] = 1;
	}
	fn = n;
	n = (n + 1) / 2;
	for (int i = 1; i < n; i++) {
		for (auto [x, y] : dp[i]) {
			for (int j = 0; j < 2; j++) {
				string now = x;
				now += 'A' + j;
				if (now.size() > MAXLEN)
					now.erase(now.begin());
				if (check(now))
					dp[i + 1][now] += y;
			}
		}
	}

	ans = 0;
	for (auto [s, cnt] : dp[n]) {
		if (check_ans(s))
			ans += cnt;
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