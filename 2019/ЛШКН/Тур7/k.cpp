#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e4 + 10;
vector<pair <int, int> > g[MAXN];

#define x first
#define y second

int n, m, k;
vector<pair <int, int> > a;


void read() {
	cin >> n >> m >> k;
	a.resize(k);
	for (auto &i : a)
		cin >> i.first >> i.second;
	sort(a.begin(), a.end());
}

void build() {
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			if (a[i].x == a[j].x || a[i].y == a[j].y) {
				int dist = abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
				if (dist > 1) {
					g[i].push_back({j, 1});
					g[j].push_back({i, 1});
				}
				else {
					g[i].push_back({j, 0});
					g[j].push_back({i, 0});
				}
			}
		}
	} 

	cout << "a = " << endl;
	for (auto i : a)
		cout << i.first << " " << i.second << endl;
	cout << "g = " << endl;
	for (int i = 0; i < k; i++) {
		cout << "i = " << i << endl;
		for (auto j : g[i]) {
			cout << j.first << " " << j.second << endl;
		}
	}
}

const int INF = 1e9 + 10;

int get_ans() {
	vector<int> dist(k, INF);
	vector<bool> used(k);
	dist[0] = 0;
	for (int i = 0; i < k; i++) {
		int v = -1;
		for (int j = 0; j < k; j++) {
			if (!used[j] && (v == -1 || dist[j] < dist[v]))
				v = j; 
		}
		if (dist[v] == INF)
			break;
		used[v] = true;

		for (auto j : g[v]) {
			if (dist[j.first] > dist[v] + j.second) {
				dist[j.first] = dist[v] + j.second;
			}
		}
	}	

	int ans = INF;

	for (int i = 0; i < n; i++) {
		if (a[i].x == n || a[i].y == m) {
			if (a[i].x == n && a[i].y == m) {
				chkmin(ans, dist[i]);
			} 
			else {
				chkmin(ans, dist[i] + 1);
			}
		}
	}
	if (ans == INF)
		ans = -1;
	return ans;
}

int ans;

void run() {
	build();
	ans = get_ans();
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