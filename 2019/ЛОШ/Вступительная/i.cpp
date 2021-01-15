#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e3 + 10;
int table[MAXN][MAXN];
bool used[MAXN][MAXN];

int n, h, w;
void read() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			table[i][j] = 0;
	cin >> n >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			string s;
			cin >> s;
			if (s == ".") {
				table[i][j] = 1;
			}
		}
	}
}

int sz = 0;

void bfs(int x, int y) {
	if (used[x][y])
		return;
	if (table[x][y] == 0)
		return;

	used[x][y] = true;
	sz++;

	bfs(x + 1, y);
	bfs(x - 1, y);
	bfs(x, y + 1);
	bfs(x, y - 1); 

	if (x % 2 == 0) {
		bfs(x - 1, y + 1);
		bfs(x + 1, y + 1);
	}
	else {
		bfs(x - 1, y - 1);
		bfs(x + 1, y - 1);
	}
}


int ans;
void run() {
	ans = 0;
	vector <int> comps;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (!used[i][j]) {
				sz = 0;
				bfs(i, j);
				comps.push_back(sz);
			}
		}
	}
	sort(comps.begin(), comps.end());
	reverse(comps.begin(), comps.end());
	for (auto i : comps) {
		n -= i;
		ans++;
		if (n <= 0)
			break;
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