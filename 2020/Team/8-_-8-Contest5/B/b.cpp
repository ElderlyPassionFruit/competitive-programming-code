#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

struct Num{
	int sum, cnt, sum2;
	Num() {
		sum = 0;
		cnt = 0;
		sum2 = 0;
	}
	Num(int x) {
		sum = x;
		cnt = 1;
		sum2 = x * x;
	}
};

Num operator+(const Num & a, const Num & b) {
	Num ans;
	ans.sum = a.sum + b.sum;
	ans.cnt = a.cnt + b.cnt;
	ans.sum2 = a.sum2 + b.sum2;
	return ans;
}

Num operator-(const Num & a, const Num & b) {
	Num ans;
	ans.sum = a.sum - b.sum;
	ans.cnt = a.cnt - b.cnt;
	ans.sum2 = a.sum2 - b.sum2;
	return ans;
}

Num operator+(const Num & a, const int & b) {
	Num ans;
	ans.sum = a.sum + b * a.cnt;
	ans.cnt = a.cnt;
	ans.sum2 = a.sum2 + a.cnt * b * b + b * 2 * a.sum;
	return ans;
}

struct Edge{
	int to, cost;
};

const int N = 1e5 + 10;
int n;
vector<Edge> g[N];

Num dp[N];

void dfsDown(int v, int p) {
	dp[v] = Num(0);
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		dfsDown(to, v);
		dp[v] = dp[v] + (dp[to] + cost);
	}
} 

void dfsUp(int v, int p) {
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		dp[to] = ((dp[v] - (dp[to] + cost)) + cost) + dp[to];
		dfsUp(to, v);
	}
}

void calcDp() {
	dfsDown(0, 0);
	dfsUp(0, 0);
	/*cout << "dp = " << endl;
	for (int i = 0; i < n; i++) {
		cout << dp[i].sum << " " << dp[i].cnt << " " << dp[i].sum2 << endl;
	}
	cout << endl;*/
}

vector<int> ans;

void makeAns() {
	int val = dp[0].sum2;
	ans.push_back(0);
	for (int i = 1; i < n; i++) {
		if (val < dp[i].sum2) continue;
		if (val > dp[i].sum2) {
			val = dp[i].sum2;
			ans.clear();
		}
		ans.push_back(i);
	}
}

signed main() {
	freopen("bfs.in", "r", stdin);
	freopen("bfs.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
	}
	calcDp();
	makeAns();
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << "\n";
	return 0;
}