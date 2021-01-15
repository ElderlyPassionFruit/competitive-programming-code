#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1000;
int n;
string a[N][2];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
}

vector<string> have;

void buildCoord() {
	for (int i = 0; i < n; i++) {
		string now = "";
		for (int len1 = 1; len1 <= a[i][0].size(); len1++) {
			now += a[i][0][len1 - 1];
			for (int len2 = 1; len2 <= a[i][1].size(); len2++) {
				now += a[i][1][len2 - 1];
				have.push_back(now);			
			}
			for (int len2 = 1; len2 <= a[i][1].size(); len2++) {
				now.pop_back();
			}
		}
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
}

int getCoord(string & s) {
	return lower_bound(all(have), s) - have.begin();
}

vector<vector<int>> g;

void buildG() {
	buildCoord();
	g.resize(n);
	for (int i = 0; i < n; i++) {
		string now = "";
		for (int len1 = 1; len1 <= a[i][0].size(); len1++) {
			now += a[i][0][len1 - 1];
			for (int len2 = 1; len2 <= a[i][1].size(); len2++) {
				now += a[i][1][len2 - 1];
				int ind = getCoord(now);
				g[i].push_back(ind);			
			}
			for (int len2 = 1; len2 <= a[i][1].size(); len2++) {
				now.pop_back();
			}
		}
	}
}

vector<int> mt, used;

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v]) {
		if (mt[i] == -1)  {
			mt[i] = v;
			return true;
		}
	}
	for (auto i : g[v]) {
		if (dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

void khun() {
	mt.assign(have.size(), -1);
	used.assign(n, -1);
	for (int i = 0; i < n; i++) {
		dfs(i, i);
	}
}

void no() {
	cout << "No solution\n";
	exit(0);
}

string ans[N];

void makeAns() {
	for (int i = 0; i < n; i++) {
		ans[i] = "";
	}
	for (int i = 0; i < (int)have.size(); i++) {
		if (mt[i] == -1) continue;
		ans[mt[i]] = have[i];
	}
	for (int i = 0; i < n; i++) {
		if (ans[i] == "") {
			no();
		}
	}
}

void run() {
	buildG();
	khun();
	makeAns();
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << ans[i] << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}