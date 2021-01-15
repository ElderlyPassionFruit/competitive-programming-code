#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

const int MAXN = 2e5 + 10;
bool used[MAXN];

void no() {
	cout << "-1" << endl;
	exit(0);
}

vector<vector<int>> ans;


set<int> pos[2];

void make() {
	for (int i = 0; i < n; i++) {
		pos[s[i] - '0'].insert(i);
	}
}

int get_next(int start, int val) {
	auto it = pos[val].lower_bound(start);
	if (it == pos[val].end()) return -1;
	return *it;
	/*for (int i = pos + 1; i < n; i++) {
		if (s[i] - '0' == val && !used[i]) {
			return i;
		} 
	}
	return -1;*/
}

void del(int start) {
	used[start] = true;
	pos[s[start] - '0'].erase(start);
}

void make(int pos) {
	vector<int> fans;
	fans.push_back(pos);
	del(pos);
	while (true) {
		int pos1 = get_next(pos, 1);
		if (pos1 == -1) break;
		int pos2 = get_next(pos1, 0);
		if (pos2 == -1) break;
		fans.push_back(pos1);
		fans.push_back(pos2);
		del(pos1);
		del(pos2);
		pos = pos2;
	}
	ans.push_back(fans);
}

void run() {
	make();
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if (s[i] == '1') no();
		make(i);
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i.size() << " ";
		for (auto j : i) {
			cout << j + 1 << " ";
		}
		cout << "\n";
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