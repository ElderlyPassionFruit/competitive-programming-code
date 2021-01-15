#include <bits/stdc++.h>

using namespace std;
#define int long long

const int INF = 1e9 + 7;
int n, m;
vector<vector<int> > help;
map <vector<int>, int> ffans;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, len, lum;
		cin >> u >> v >> len >> lum;
		u--;
		v--;
		help.push_back({u, v, len, lum});
		help.push_back({u, v, len, lum});
		ffans[{u, v, len, lum}] = i + 1;
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

int ans = INF;
vector<int> fans;

void run() {
	for (int i = 1; i <= 2 * m; i++) {
		vector<int> mask(2 * m);
		for (int j = 0; j < i; j++) {
			mask[2 * m - 1 - j] = 1;
		}

		do {
			vector<vector<int> > ed;
			for (int j = 0; j < 2 * m; j++)
				if (mask[j])
					ed.push_back(help[j]);
			sort(ed.begin(), ed.end());
			do {
				int fcheck = check(ed);
				if (fcheck < ans) {
					ans = fcheck;
					fans.clear();
					for (auto j : ed)
						fans.push_back(ffans[j]);
				}
			} while(next_permutation(ed.begin(), ed.end()));
		} while(next_permutation(mask.begin(), mask.end()));
	}
}

void write() {
	if (ans == INF) {
		cout << "-1";
	}
	cout << ans << "\n";
	for (auto i : fans) {
		cout << i << " ";
	}
	cout << "\n";
}

signed main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
3 4
2 2 7 4
3 2 3 8
3 1 8 8
2 3 1 7
*/

/*
3 4
1 3 3 7
1 3 3 9
2 2 10 2
2 3 2 8
10
1 4 4 2 

*/
