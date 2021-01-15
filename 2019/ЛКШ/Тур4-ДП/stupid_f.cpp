#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<pair <pair <int, int>, int> > g;
int n, k;
void read() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		g.push_back({{u, v}, c});
	}
}

int check(vector<int> a) {
	map <int, int> help;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			help[g[i].first.first]++;
			help[g[i].first.second]++;
			sum += g[i].second;
		}
	}
	for (auto i : help) {
		if (i.second > 1)
			return -1e18;
	}
	return sum;
}

int ans;

void run() {
	vector<int> a(n - 1, 0);
	for (int i = 0; i < k; i++) {
		a[n - 2 - i] = 1;
	}
	ans = -1e18;
	do{
		chkmax(ans, check(a));
	} while(next_permutation(a.begin(), a.end()));
	
	if (ans == -1e18) {
		cout << "Impossible" << endl;
		exit(0);
	}
}

void write() {
	cout << ans << endl;
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