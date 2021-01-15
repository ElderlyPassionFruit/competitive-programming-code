#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
string s;

void read() {
	cin >> n >> k;
	cin >> s;
}

set<pair<int, int> > used;
set<pair<int, int> > ans;

map<char, int> help = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

bool check(int x, int y) {
	return used.count({x - 1, y}) && used.count({x, y - 1}) && used.count({x - 1, y - 1});
}

void dfs(int x, int y, int day, int it) {
	used.insert({x, y});
	//if (check(x, y)) ans.insert({x, y});
	if (day == n) day = 0, it++;
	if (it == k) return;
	dfs(x + dx[help[s[day]]], y + dy[help[s[day]]], day + 1, it);
}

void run() {
	dfs(0, 0, 0, 0);
	for (auto i : used) {
		if (check(i.first, i.second)) {
			ans.insert(i);
		}
	}
}

void write() {
	cout << ans.size() << endl;
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