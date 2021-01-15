#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 410;
char g[MAXN][MAXN];
int n, k;
vector<vector<int> > a;
void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			cin >> g[i][j];
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		vector<int> fk;
		while (cin >> x) {
			if (x == n) break;
			fk.push_back(x);
		}
		a.push_back(fk);
	}
}

vector<int> ans;

vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> ans;
	while (!a.empty() && !b.empty()) {
		int v = a.back();
		a.pop_back();
		int u = b.back();
		b.pop_back();
		if (g[v][u] == '-') {
			a.push_back(v);
			ans.push_back(u);
		}
		else {
			b.push_back(u);
			ans.push_back(v);
		}
	}

	while (!a.empty()) {
		ans.push_back(a.back());
		a.pop_back();
	}
	while (!b.empty()) {
		ans.push_back(b.back());
		b.pop_back();
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

void run() {
	vector<int> now = a[0];
	for (int i = 1; i < k; i++) {
		now = merge(now, a[i]);
	}
	ans = now;	
}

void write() {
	cout << 1 << " ";
	for (auto i : ans)
		cout << i << " ";
	cout << n << endl;
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