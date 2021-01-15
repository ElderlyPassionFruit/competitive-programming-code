#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
const int MAXN = 1e5 + 10;
int n;
int a[MAXN];

int par[MAXN], sz[MAXN], mx[MAXN];
bool used[MAXN];

void init() {
	iota(par, par + n, 0);
	iota(mx, mx + n, 0);
	fill(sz, sz + n, 1);
	fill(used, used + n, 0);
}

int getPar(int v) {
	if (par[v] == v) return v;
	return par[v] = getPar(par[v]);
}

void uni(int a, int b) {
	a = getPar(a);
	b = getPar(b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a, b);
	par[b] = a;
	sz[a] += sz[b];
	mx[a] = max(mx[a], mx[b]);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> q;
	init();
	for (int i = 0; i + 1 < n; i++) {
		if (a[i] > a[i + 1]) {
			q.push_back(i);
		}
	}
	int ans = 0;
	while (!q.empty()) {
		/*cout << "q = " << endl;
		for (auto i : q) {
			cout << i << " ";
		}
		cout << endl;*/
		for (auto i : q) {
			int myR = mx[getPar(i)];
			if (myR == n - 1) continue;
			int nxt = myR + 1;
			assert(!used[nxt]);
			//cout << "i = " << i << " nxt = " << nxt << endl;
			//cout << "i = " << i << " nxt = " << nxt << endl;
			if (a[i] <= a[nxt]) continue;
			used[nxt] = true;
			uni(i, nxt);
		}
		/*cout << "used = " << endl;
		for (int i = 0; i < n; i++) {
			cout << used[i] << " ";
		}
		cout << endl;
		cout << "par = " << endl;
		for (int i = 0; i < n; i++) {
			cout << mx[getPar(i)] << " "; 
		}
		cout << endl;*/
		vector<int> nq;
		for (auto i : q) {
			if (used[i]) continue;
			int myR = mx[getPar(i)];
			if (myR == n - 1) continue;
			int nxt = myR + 1;
			//cout << "i = " << i << " myR = " << myR << " nxt = " << nxt << endl;
			assert(!used[nxt]);
			if (a[i] > a[nxt]) {
				nq.push_back(i);
			}
		}
		q = nq;
		ans++;
	}
	cout << ans << endl;
	return 0;
}