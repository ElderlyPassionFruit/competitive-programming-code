#include <bits/stdc++.h>

using namespace std;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

map <pair <char, char>, vector<pair <pair <char, char>, int> > > g, gr;
int n;
set<pair <char, char> > vert;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		char a, b, c;
		cin >> a >> b >> c;
		g[{a, b}].push_back({{b, c}, i});
		gr[{b, c}].push_back({{a, b}, i});
		vert.insert({a, b});
		vert.insert({b, c});
	}
}

vector <pair <char, char> > path, ans;

void dfs(pair <char, char> v) {
	while (!g[v].empty()) {
		auto i = g[v].back();
		g[v].pop_back();
		dfs(i.first);
		path.push_back(i.first);
	}
}

void run() {
	int cnt = 0;
	for (auto i : vert) {
		cnt += g[i].size() != gr[i].size();
	}

	for (auto i : vert) {
		if (abs((int)g[i].size() - (int)gr[i].size()) > 1) {
			cout << "NO" << endl;
			exit(0);
		}
	}

	if (cnt > 2) {
		cout << "NO" << endl;
		exit(0);
	}
	if (cnt == 0) {
		for (auto i : g) {
			dfs(i.first);
			path.push_back(i.first);
			reverse(path.begin(), path.end());
			ans = path;
			return;
		}
	}

	pair <char, char> null = {'-', '-'};

	pair <char, char> v = null, u = null;
	for (auto i : vert) {
		if (g[i].size() > gr[i].size()) {
			v = i;
		}
		if (g[i].size() < gr[i].size()) {
			u = i;
		}
	}

	if (v == null || u == null) {
		cout << "NO" << endl;
		exit(0);
	}

	dfs(v);
	path.push_back(v);
	reverse(path.begin(), path.end());
	//cerr << "path = " << endl;
	//for (auto i : path) {
	//	cerr << i.first << " " << i.second << endl;
	//}
	ans = path;
	//for (int i = 1; i < n + 2; i++) {
	//	path.push_back(path[i]);
	//}

	/*for (int i = 0; i < path.size(); i++) {
		if (path[i] == u && path[i + 1] == v) {
			for (int j = i + 1; j <= i + 1 + n; j++) {
				ans.push_back(path[j]);
			}
			return;
		}
	}*/
}

string make(vector <pair <char, char> > path) {
	int sz = path.size();
	string ans = "";
	if (sz == 0) {
		return ans;
	}
	for (int i = 0; i < sz - 1; i++) {
		ans += path[i].first;
	}
	ans += path.back().first;
	ans += path.back().second;
	return ans;
}

void write() {
	auto fout = make(ans);
	//cerr << fout << endl;
	if (fout.size() != n + 2) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	cout << fout << endl;
}

signed main() {
	freopen("password.in", "r", stdin);
	freopen("password.out", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
5
aca
aba
aba
cab
bac
*/