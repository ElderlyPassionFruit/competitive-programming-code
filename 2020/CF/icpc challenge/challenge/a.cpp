#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));
const int MAXN = 2e5;
int n, m;
vector<int> g[MAXN];
vector<vector<int>> ans;

void read() {
	int u, v;
	while (cin >> u >> v) {
		g[u].push_back(v);
		g[v].push_back(u);
		chkmax(n, u + 1);
		chkmax(n, v + 1);
		m++;
	}
	cerr << "n = " << n << " m = " << m << endl;
}

bool used[MAXN];
ld fans = -1e9;
vector<vector<int>> bestAns;

int calcEinC(vector<int> & c) {
	int EinC = 0;
	for (auto i : c) used[i] = true;
	for (auto i : c) {
		for (auto j : g[i]) {
			if (used[j] && i > j) {
				EinC++;
			}
		}
	}
	for (auto i : c) used[i] = false;
	return EinC;
}

int calcDeg(vector<int> & c) {
	int Deg = 0;
	for (auto i : c) {
		Deg += g[i].size();
	}
	return Deg;
}

ld sq(ld x) {
	return x * x;
}

ld calcModularity() {
	ld have = 0;	
	for (auto c : ans) {
		have += (ld)calcEinC(c) / m - sq((ld)calcDeg(c) / (2 * m));
	}
	return have;
}

ld calcDensity(vector<int> & c) {
	if (c.size() == 1) return 1;
	return (ld) 2 * calcEinC(c) / (c.size() * (c.size() - 1));
}

ld calcRegularization() {
	ld have = 0;
	for (auto i : ans) {
		have += calcDensity(i);
	}
	have -= (ld)n / ans.size();
	have /= 2;
	return have;
}

ld calc() {
	ld Modularity = calcModularity(), Regularization = calcRegularization();
	cerr << "calcModularity = " << Modularity << " calcRegularization = " << Regularization << endl;
	return Modularity; //+ Regularization;	
}

void check() {
	ld now = calc();
	now += 1;
	now *= 100000;
	cerr << "now = " << now << " fans = " << fans << endl;
	if (now <= fans) return;
	fans = now;
	bestAns = ans;
}

void BFS(vector<int> & color, queue<int> & q, vector<int> & dist, int myDist) {
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : g[v]) {
			if (color[i]) continue;
			color[i] = color[v];
			dist[i] = dist[v] + 1;
			if (myDist != dist[i])
				q.push(i);
			ans[color[i] - 1].push_back(i);
		}
	}
}

void BFS() {
	int bloks = 2000;
	vector<int> color(n, 0);
	vector<int> dist(n, 0);
	set<int> have;
	for (int i = 0; i < n; i++) {
		have.insert(i);
	}
	for (int i = 0; i < bloks; i++) {
		if (have.empty()) break;
		auto it = have.lower_bound(rnd() % n);
		if (it == have.end()) {
			it = have.begin();
		}
		int v = *it;
		have.erase(v);
		color[v] = i + 1;
		ans.push_back({v});
		queue<int> q;
		q.push(v);
		int myDist = rnd() % 1000;
		BFS(color, q, dist, myDist);
	} 
	ans.push_back({});
	for (int i = 0; i < bloks; i++) {
		if (!color[i]) {
			color[i] = bloks + 1;
			ans[ans.size() - 1].push_back(i);
		}
	}
	check();
}

void run() {
	for (int it = 0; it < 100; it++) {
		BFS();
	}
}

void write() {
	for (auto i : bestAns) {
		if (i.empty()) continue;
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
}

signed main() {
	cout.precision(20);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}