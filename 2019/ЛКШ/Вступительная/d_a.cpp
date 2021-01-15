#include <bits/stdc++.h>

using namespace std;
#define int long long

vector <vector <int> > g;

bool check(vector <int> a, vector <int> b) {
	return a[0] >= b[1] && a[0] <= b[2] && b[0] >= a[1] && b[0] <= a[2]; 
}

int n;
int k;
int cnt;

void read() {
	cin >> cnt;
	vector <vector <int> > a, b;
	for (int i = 0; i < cnt; i++) {
		int x, y, z, t;
		cin >> x >> y >> z >> t;
		if (x > z)
			swap(x, z);
		if (y > t)
			swap(y, t);
		if (x == z) {
			a.push_back({x, y, t});
		}
		else {
			b.push_back({y, x, z});
		}
	}

	n = a.size();
	k = b.size();
	g.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (check(a[i], b[j]))
				g[i].push_back(j);
		}
	}
}


int ans;
vector <int> mt;
vector <int> used;

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (auto i : g[v]) {
		if (mt[i] == -1 || dfs(mt[i])) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}


void run() {
	mt.assign(k, -1);
	for (int i = 0; i < n; i++) {
		used.assign(n, 0);
		dfs(i);
	}

	int fans = 0;
	for (int i = 0; i < k; i++) {
		if (mt[i] != -1)
			fans++;
	}
	ans = cnt - fans;
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