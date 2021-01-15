#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e9 + 7;
int n, m;
vector<vector <int> > help;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		help.push_back({a, b, c, d});
	}
}

int check(vector<vector<int>> ed) {
	int cost = 0;
	int v = 0;
	int lum = 0;
	bool flag = false;
	for (int i = 0; i < ed.size(); i++) {
		auto p = ed[i];
		if (p[0] != v && p[1] != v)
			return INF;
		if (p[1] == v)
			swap(p[0], p[1]);
		if (lum > p[3])
			return INF;
		lum = p[3];
		cost += p[2];
		v = p[1];
		if (v == 1)
			flag = true;
	}	
	if (!flag || v != 0)
		return INF;
	return cost;
}

bool ans = true;
void run() {	
	int cost;
	cin >> cost;
	vector<int> mask;
	int x;
	while (cin >> x) {
		mask.push_back(x - 1);
	}
	vector<vector<int> > ed;
	for (auto i : mask)
		ed.push_back(help[i]);
	int fcost = check(ed);
	if (fcost != cost)
		ans = false;
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("fin.txt", "r", stdin);
	freopen("fout.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}