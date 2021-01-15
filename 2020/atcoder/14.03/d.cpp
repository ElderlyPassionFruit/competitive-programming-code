#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;	
}

set<string> have;
vector<string> ans;

void gen(string now, int cnt) {
	if (have.count(now)) return;
	have.insert(now);
	if (now.size() == n) {
		ans.push_back(now);
		return;
	}
	for (int i = 0; i < cnt; i++) {
		now += 'a' + i;
		gen(now, cnt);
		now.pop_back();
	}
	now += 'a' + cnt;
	gen(now, cnt + 1);
}

void run() {
	gen({}, 0);
}

void write() {
	sort(all(ans));
	for (auto i : ans ){
		cout << i << "\n";
	}
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