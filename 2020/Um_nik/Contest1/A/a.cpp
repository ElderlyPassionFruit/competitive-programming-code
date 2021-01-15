#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
int n;
int type[MAXN];
int p[MAXN];
int deg[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> type[i];
	}
	fill(p, p + n, -1);
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		if (!v) continue;
		v--;
		p[i] = v;
		deg[v]++;
	}
	vector<int> ans = {};
	for (int i = 0; i < n; i++) {
		if (!type[i]) continue;
		vector<int> fans;
		int now = i;
		while (now != -1 && (now == i || deg[now] == 1)) {
			fans.push_back(now);
			now = p[now];
		}
		if (fans.size() > ans.size()) {
			ans = fans;
		}
	}
	reverse(all(ans));
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << endl;
	return 0;
}