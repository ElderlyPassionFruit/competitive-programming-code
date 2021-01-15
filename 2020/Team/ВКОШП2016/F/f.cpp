#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 5000 + 179;

int arr[MAXN][MAXN];
int pi[MAXN], pj[MAXN];

const int MOD = 1e9 + 7;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int h, w, n;
	cin >> h >> w >> n;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			arr[i][j]= i * w + j;
		}
	}
	for (int i = 0; i < h; i++) {
		pi[i] = i;
	}
	for (int i = 0; i < w; i++) {
		pj[i] = i;
	}
	string s;
	cin >> s;
	int szz;
	cin >> szz;
	vector<int> ax(szz);
	for (int &el : ax) {
		cin >> el;
	}
	while (ax.size() < n) {
		ax.push_back((10007 * ax[ax.size() - 2] + 10009 * ax[ax.size() - 1] + 87277) % h);
	}
	cin >> szz;
	vector<int> bx(szz);
	for (int &el : bx) {
		cin >> el;
	}	
	while (bx.size() < n) {
		bx.push_back((10007 * bx[bx.size() - 2] + 10009 * bx[bx.size() - 1] + 87277) % w);
	}
	cin >> szz;
	vector<int> cx(szz);
	for (int &el : cx) {
		cin >> el;
	}
	while (cx.size() < n) {
		cx.push_back((10007 * cx[cx.size() - 2] + 10009 * cx[cx.size() - 1] + 87277) % h);
	}
	cin >> szz;
	vector<int> dx(szz);
	for (int &el : dx) {
		cin >> el;
	}	
	while (dx.size() < n) {
		dx.push_back((10007 * dx[dx.size() - 2] + 10009 * dx[dx.size() - 1] + 87277) % w);
	}
	for (int i = 0; i < n; i++) {
		if (s[i] == 'c') {
			swap(pj[bx[i]], pj[dx[i]]);
		} else if (s[i] == 'r') {
			swap(pi[ax[i]], pi[cx[i]]);
		} else {
			swap(arr[pi[ax[i]]][pj[bx[i]]], arr[pi[cx[i]]][pj[dx[i]]]);
		}
	}
	int ans = 0;
	int cur17 = 1;
	for (int i = 0; i < h; i++) {
		int cur19 = 1;
		for (int j = 0; j < w; j++) {
			ans += (ll) arr[pi[i]][pj[j]]  % MOD * cur17 % MOD * cur19 % MOD;
			ans %= MOD;
			ans += MOD;
			ans %= MOD;
			cur19 = (ll) cur19 * 19 % MOD;
		}
		cur17 = (ll) cur17 * 17 % MOD;
	}
	ans %= MOD;
	ans += MOD;
	ans %= MOD;
	cout << ans << endl;
	return 0;
}