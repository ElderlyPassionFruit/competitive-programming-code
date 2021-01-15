#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18;
const int MAXN = 2010, MAXM = 1e5 + 10;
vector<pair<pair <int, int>, int> > g[MAXN];
vector<pair <int, int> > good[MAXM];
vector<pair <int, int> > ed;
int costs[MAXM];
int last[MAXM];
int have_time;
int n, m, k;
void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		cost *= 2;
		costs[i] = cost;
		g[u].push_back({{v, cost}, i + 1});
		g[v].push_back({{u, cost}, i + 1});
		ed.push_back({u, v});
	}
}

void calc() {
	int t = 0;
	for (int i = 0; i < k; i++) {
		int ind, t1;
		cin >> ind >> t1;
		t1 *= 2;
		ind--;
		int helpt = t - last[ind] - 2;
		if (helpt >= costs[ind]) {
			good[ind].push_back({last[ind] + 1, t - 1});
		}
		t += t1;
		last[ind] = t;	
	}
	for (int i = 0; i < m; i++)
		good[i].push_back({last[i] + 1, INF});
	have_time = t;
}

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.first < b.first || (a.first == b.first && a.second < b.second);
}

int get(int v, int u, int t, int len, int ind) {
	ind--;
	for (int pos = 0; pos < good[ind].size(); pos++) {
		if (good[ind][pos].second >= max(good[ind][pos].first, t) + len)
			return max(good[ind][pos].first, t) + len;
	}
}

vector<int> ans;

void run() {
	calc();

	vector<int> t(n, INF);
	vector<int> p(n, -1);
	t[0] = 0;
	set<pair <int, int> > q;
	q.insert({0, 0});
	while (!q.empty()) {
		auto p1 = *q.begin();
		q.erase(q.begin());
		int v = p1.second;
		int t1 = p1.first;
		for (auto i : g[v]) {
			int need = get(v, i.first.first, t1, i.first.second, i.second);
			if (t[i.first.first] > need) {
				q.erase({t[i.first.first], i.first.first});
				t[i.first.first] = need;
				p[i.first.first] = i.second - 1;
				q.insert({t[i.first.first], i.first.first});
			}
		}
	}

	if (t[n - 1] >= have_time)
		return;

	int pos = n - 1;
	while (p[pos] != -1) {
		ans.push_back(p[pos] + 1);
		pos ^= ed[p[pos]].first ^ ed[p[pos]].second;
	}
	reverse(ans.begin(), ans.end());
}

void write() {
	if (ans.size() == 0) {
		cout << "NO\n";
	}
	else {
		cout  << "YES\n";
		cout << ans.size() << " ";
		for(auto i : ans)
			cout << i << " ";
		cout  << "\n";
	}
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