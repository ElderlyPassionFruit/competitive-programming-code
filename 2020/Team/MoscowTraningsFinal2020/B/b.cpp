#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e4 + 228;

int n;
int x[MAXN], y[MAXN];

int get(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
} 

bool used[MAXN];
int min_e[MAXN];
const int INF = INT_MAX;
	
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	fill(min_e, min_e + n, INF);
	
	min_e[0] = 0;
	ll ans = 0;

	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j =0 ; j < n; j++) {
			if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
				v = j;
			}
		}
	
		ans += min_e[v];
		used[v] = true;

		for (int to = 0; to < n; ++to) {
			int g = get(v, to);
			if (g < min_e[to]) {
				min_e[to] = g;
			}
		}
	}
	cout << ans * 2LL << endl;
	return 0;
}