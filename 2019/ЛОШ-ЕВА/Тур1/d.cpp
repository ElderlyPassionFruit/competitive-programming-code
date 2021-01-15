#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;

vector<vector<char> > table;

vector<pair <int, int> > cnt() {
	vector<pair <int, int> > ans;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (table[i][j] == 'Q')
				ans.push_back({i, j});
	return ans;
}

#define x first
#define y second

bool check(pair <int, int> a, pair <int, int> b) {
	return (a.x == b.x) || (a.y == b.y) || (a.x + a.y == b.x + b.y) || (a.x - a.y == b.x - b.y);
}

string make(pair <int, int> a, pair <int, int> b) {
	table[a.x][a.y] = '.';
	string ans = "";
	ans += 'a' + a.y;
	ans += '8' - a.x;
	ans += ":";
	ans += 'a' + b.y;
	ans += '8' - b.x;
	return ans;
}

void dfs(int v, vector<bool> &used, vector<vector<int> > &g) {
	used[v] = true;
	for (auto i : g[v])
		if (!used[i])
			dfs(i, used, g);
}

void no() {
	cout << "NO SOLUTION" << endl;
	exit(0);
}

string solve() {
	auto pos = cnt();
	int sz = pos.size();
	vector<vector<int> > g(sz);
	for (int i = 0; i < sz; i++){
		for (int j = i + 1; j < sz; j++){
			if (check(pos[i], pos[j])) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
	vector<bool> used(sz, false);
	dfs(0, used, g);
	for (int i = 0; i < sz; i++)
		if (!used	[i])
			no();
	/*cout << "g = " << endl;
	for (auto i : g){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}*/

	for (int i = 0; i < sz; i++)
		if (g[i].size() == 1)
			return make(pos[i], pos[g[i][0]]);

	return make(pos[0], pos[g[0][0]]);
}

void read() {
	n = 8;
	table.assign(8, vector<char> (8));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> table[i][j];
}

vector<string> ans;

void run() {
	while (cnt().size() > 1) {
		ans.push_back(solve());
	}
}

void write() {
	for (auto i : ans)
		cout << i << endl;
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