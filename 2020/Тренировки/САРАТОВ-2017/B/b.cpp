#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 110;
int n, p[MAXN];
bool used[MAXN];
int ans = 0;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i], p[i]--;
	}
	int now = 0;
	while (!used[now]) {
		ans++;
		used[now] = true;
		now = p[now];
	}
	cout << ans << endl;
	return 0;
}