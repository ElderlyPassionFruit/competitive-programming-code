#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18 + 10;

struct get_min{
	vector<pair <int, int> > t;
	vector<int> a;
	int n;

	void init(int sz) {
		n = sz;
		t.assign(n, {INF, -1});
		a.assign(n, INF);
	}

	pair <int, int> getmin(int r) {
		pair <int, int> ans = {INF, -1};
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
			ans = min(ans, t[i]);
		return ans;
	}

	int get(int r) {
		return getmin(r).first;
	}

	int get_pred(int r) {
		return getmin(r).second;
	}

	int get_element(int r) {
		return a[r];
	}

	void upd(int pos, int val, int pred) {
		pair <int, int> new_val = {val, pred};
		for (int i = pos; i < n; i = (i | (i + 1)))
			t[i] = min(t[i], new_val);
		a[pos] = val;
	}

	void init(vector<int> arr) {
		init ((int) arr.size());
		a = arr;
		for (int i = 0; i < a.size(); i++)
			upd(i, a[i], -1);
	}
};

const int MAXN = 1e5 + 10;
vector <pair <int, pair <int, int> > > g[MAXN];
unordered_map<int, vector<int>> edges;
map<vector <int>, int> for_edges;
int n, m;

bool cmp(pair <int, pair <int, int> > a, pair <int, pair <int, int> > b) {
	return a.second < b.second;
}

bool better(pair <int, pair <int, int> > a, pair <int, pair <int, int> > b) {
	return a.second.second < b.second.second;
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, len, lum;
		cin >> u >> v >> len >> lum;
		u--;
		v--;
		edges[i] = {u, v, len, lum};
		for_edges[{u, v, len, lum}] = i;
		for_edges[{v, u, len, lum}] = i;
		g[u].push_back({v, {lum, len}});
		g[v].push_back({u, {lum, len}}); 
	}
	for (int i = 0; i < n; i++) {
		if (g[i].size() == 0)
			continue;
		sort(g[i].begin(), g[i].end(), cmp);
	}

}

pair <vector<map<int, int> >, vector<get_min> > solve(int s, int f, vector <int> &start, bool flag) {
	//cout << endl;
	vector <map<int, int> > positions(n);
	vector <get_min> nodes(n);
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < g[i].size(); j++) {
			if (positions[i].count(g[i][j].second.first))
				continue;
			positions[i][g[i][j].second.first] = cnt++;
		}
		if (i != s)
			nodes[i].init(g[i].size());
	}
	nodes[s].init(start);

	/*cout << "positions = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : positions[i]) {
			cout << j.first << " ";
		}
		cout << endl;
		for (auto j : positions[i]) {
			cout << j.second << " ";
		}
		cout << endl;
	}

	cout << endl;


	cout << "nodes = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		cout << "a = ";
		for (auto j : nodes[i].a)
			cout << j << " ";
		cout << endl;
		cout << "t = ";
		for (auto j : nodes[i].t)
			cout << j.first << " " << j.second << endl;
		cout << endl; 
	}
	cout << endl;
	*/
	set <pair <pair <int, int> , int> > q;
	if (flag) {
		for (int i = 0; i < g[s].size(); i++) {
			q.insert({{start[i], g[s][i].second.first}, s});
		}
	}
	else {
		q.insert({{0LL, 0LL}, s});
	}
	
	/*cout << "q = " << endl;
	for (auto i : q) {
		cout << i.first.first << " " << i.first.second << " " << i.second << endl;
	}*/

	while (!q.empty()) {

		auto x = *q.begin();
		q.erase(q.begin());
		int v = x.second;
	//	cout << "v = " << v << endl;
		//int dist = nodes[v].get(positions[v][lum_v]);
		for (auto j : g[v]) {
	
			int u = j.first;
			int len = j.second.second;
			int lum_u = j.second.first;

			int can = nodes[u].get(positions[u][lum_u]);
			int dist = nodes[v].get(positions[v][lum_u]);



	//		cout << "can = " << can << " dist = " << dist << " len = " << len << endl;
  
			if (can > len + dist) {
				//..q.erase({{can, lum_u}, u});
				can = len + dist;
				nodes[u].upd(positions[u][lum_u], can, for_edges[{u, v, len, lum_u}]);
				q.insert({{can, lum_u}, u});
			}
	
		}
	}

	start.resize((int)g[f].size());
	for (int i = 0; i < start.size(); i++)
		start[i] = nodes[f].get_element(i);
	return {positions, nodes};
}

int ans_len;
vector <int> ans_path;

void get_ans(int s, int f, int &lum, vector <get_min> & nodes, vector <map<int, int> > & positions) {
	while (s != f) {
		//cout << "f = " << f << " lum = " << lum << endl;
		int pos = nodes[f].get_pred(positions[f][lum]);
		//cout << "pos = " << pos << endl; 
		auto p = edges[pos];
		int v = p[0];
		int u = p[1];
		int len = p[2];
		int lum_path = p[3];
		//cout << "v = " << v << " u = " << u << " len = " << len << " lum_path = " << lum_path << endl;
		if (u == f)
			swap(u, v);
		ans_len += len;
		lum = lum_path;
		ans_path.push_back(pos + 1);
		f = u;
	}
}

void run() {
	vector <int> start;
	for (int i = 0; i < g[0].size(); i++)
		start.push_back(0);
	

	/*cout << "start = " << endl;
	for (auto i : start)
		cout << i << " ";
	cout << endl;
	cout << endl;*/

	auto to = solve(0, 1, start, false);
	
/*	cerr << "to" << endl;
	cout << "start = " << endl;
	for (auto i : start)
		cout << i << " ";
	cout << endl;
	cout << endl;	
*/
	auto from = solve(1, 0, start, true);
		
/*	cerr << "from" << endl;
	cout << "start = " << endl;
	for (auto i : start)
		cout << i << " ";
	cout << endl;
	cout << endl;	*/

	auto positions = from.first;
	auto nodes = from.second;

	int s, f, lum;

	ans_len = 0;
	s = 1, f = 0, lum = (g[f].back()).second.first;
	get_ans(s, f, lum, nodes, positions);
	
	positions = to.first;
	nodes = to.second;
	s = 0, f = 1;
	get_ans(s, f, lum, nodes, positions);

	reverse(ans_path.begin(), ans_path.end());
}

void write() {
	cout << ans_len << "\n";
	for (auto i : ans_path)
		cout << i << " ";
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