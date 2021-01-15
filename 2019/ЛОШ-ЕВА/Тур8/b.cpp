#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m, q;
vector<int> a;
void read() {
	cin >> n >> m >> q;
	a.resize(m);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		a[x]++;
	}
}

vector<pair<int, int>> query;
vector<int> ans;

void run() {
	ans.resize(q);
	for (int i = 0; i < q; i++) {
		int x;
		cin >> x;
		x -= n + 1;
		query.push_back({x, i});
	}
	
	sort(query.begin(), query.end());
	
	set<pair<int, int> > help;
	for (int i = 0; i < m; i++)
		help.insert({a[i], i});

	int pos = 0;
	int year = 0;
	
	/*cout << "query = " << endl;
	for (auto i : query)
		cout << i.first << " " << i.second << endl;
	*/
	while (pos < q) {
		while (year != query[pos].first) {
			auto p = *help.begin();
			help.erase(help.begin());
			p.first++;
			help.insert(p);
			year++;
		}
		auto p = *help.begin();
		help.erase(help.begin());
		p.first++;
		help.insert(p);
		while (pos < q && query[pos].first == year){
			ans[query[pos++].second] = p.second + 1;
		}
		year++;
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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