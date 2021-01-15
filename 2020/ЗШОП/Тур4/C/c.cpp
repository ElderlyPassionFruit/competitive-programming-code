#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
string s;

void read() {
	cin >> s;
}

struct segment{
	char L, R;
	int ans;
	segment() {
		L = '0';
		R = '0';
		ans = 0;
	}
	segment(char _L, char _R, int _ans) {
		L = _L;
		R = _R;
		ans = _ans;
	} 
};

segment merge(segment a, segment b) {
	segment ans(a.L, b.R, a.ans + b.ans - (a.R == b.L));
	return ans;
}

segment mul(segment a, int b) {
	if (b == 1) return a;
	if (b % 2 == 0) {
		return mul(merge(a, a), b / 2);
	}
	else {
		return merge(a, mul(a, b - 1));
	}
}

pair<string, string> split(string s) {
	int bal = 0;
	int pos = -1;
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i] == '(') bal++;
		if (s[i] == ')') bal--;
		if (bal == 0)
			pos = i;
	}
	if (pos == -1) return {"", ""};
	pair<string, string> ans = {"", ""};
	for (int i = 0; i <= pos; i++)
		ans.first += s[i];
	for (int i = pos + 1; i < s.size(); i++)
		ans.second += s[i];
	return ans;
}

bool check(string s) {
	for (auto i : s) {
		if (i != 'A' && i != 'B') 
			return false;
	}
	return true;
}

segment stupid_solve(string s) {
	segment ans(s[0], s[0], 1);
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == ans.R) continue;
		ans.ans++;
		ans.R = s[i];
	}
	return ans;
}

segment solve(string s) {
	//cout << s << endl;
	auto help = split(s);
	pair<string, string> fcheck = {"", ""};
	if (check(s)) 
		return stupid_solve(s);
	if (help != fcheck) 
		return merge(solve(help.first), solve(help.second));
	int now = 0;
	string fans = "";
	bool flag = false;
	for (int i = 1; i < s.size() - 1; i++) {
		if (s[i] == ',' && !flag) {
			flag = true;
			continue;
		}
		if (!flag)
			now *= 10, now += s[i] - '0';
		else
			fans += s[i];
	}
	return mul(solve(fans), now);
}

int ans;

void run() {
	ans = solve(s).ans;
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