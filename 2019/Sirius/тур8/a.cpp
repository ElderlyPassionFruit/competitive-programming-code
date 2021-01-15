#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e5 + 10;
pair <int, int> ans;
int pref[MAXN];
int cost[MAXN];
vector <pair <int, int> > h;
int n;

void read() {
	cin >> n;
	h.assign(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> h[i].first;
	}
	for (int i = 1; i <= n; i++) {
		cin >> h[i].second;
	}
	sort(h.begin(), h.end());
	/*cerr << "h = " << endl;
	for (int i = 1; i <= n; i++) {
		cerr << h[i].first << " ";
	}
	cerr << endl;
	for (int i = 1; i <= n; i++) {
		cerr << h[i].second << " ";
	}
	cerr << endl;*/
}
const int INF = 1e18;
void run() {
	pref[n] = 0;
	cost[n] = h[n].second;
	for (int i = n - 1; i >= 1; i--) {
		pref[i] = pref[i + 1] + (h[i + 1].first - h[i].first) * cost[i + 1];
		cost[i] = cost[i + 1] + h[i].second;
	}

	ans  = make_pair(1e18, 1e18);
	int sum_cost = 0;
	int delta = 0;
	for (int i = 1; i <= n; i++) {
		sum_cost += h[i].second;
		pair <int, int> fans;
		pair <int, int> l, r;
		l.first = h[i].first;
		l.second = sum_cost;
		r.first = h[i + 1].first;
		r.second = cost[i + 1];
		if (l.second < r.second) {
			fans = {r.first, sum_cost * (r.first - l.first) + pref[i + 1] + delta};
		}
		else {
			fans = {l.first, cost[i + 1] * (r.first - l.first) + pref[i + 1] + delta};
		}
		if (fans.second < ans.second || (fans.second == ans.second && fans.first < ans.second)) {
			ans = fans;
		}
		delta += (h[i + 1].first - h[i].first) * sum_cost;
	}
}

void write() {
	cout << ans.first << " " << ans.second << endl;
}

signed main() {
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}