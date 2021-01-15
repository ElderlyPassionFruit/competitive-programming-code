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

vector<pair <int, int> > help;

int solve(int k) {
	for (int i = 0; i + 1 < help.size(); i++) {
		int dist = (help[i + 1].first - help[i].first) * (i + 1);
		if (dist <= k) {
			k -= dist;
			continue;
		}
		k %= (i + 1);
		vector<int> help2(i + 1);
		for (int j = 0; j <= i; j++) {
			help2[j] = help[j].second;
		}
		sort(help2.begin(), help2.end());
		return help2[k] + 1;
	}
	k %= help.size();
	vector<int> help2(m);
	for (int j = 0; j < help.size(); j++) {
		help2[j] = help[j].second;
	}
	sort(help2.begin(), help2.end());
	return help2[k] + 1;
}

vector<int> ans;

void run() {
	for (int i = 0; i < a.size(); i++)
		help.push_back({a[i], i});
	sort(help.begin(), help.end());
	for (int test = 0; test < q; test++) {
		int k;
		cin >> k;
		ans.push_back(solve(k - n - 1));
	}
}

void write() {
	for (auto i : ans)
		cout << i << endl;
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