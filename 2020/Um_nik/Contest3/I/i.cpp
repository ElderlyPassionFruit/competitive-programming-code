#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
const int MOD = 1e3 + 9;
const ld PI = acos(-1);
using cd = complex<double>;

int getLog(int n) {
	int ans = 0;
	while (n) {
		ans++;
		n /= 2;
	}
	return ans - 1;
}

const int MAXN = (1 << 18) + 10;
cd w[MAXN];
int rev[MAXN];

void initFFT(int n, int & LOG) {
	LOG = getLog(n);
	for (int i = 0; i < n; i++) {
		w[i] = cd(cos(2 * PI * i / n), sin(2 * PI * i / n));
	}
	rev[0] = 0;
	for (int mask = 1; mask < n; mask++) {
		rev[mask] = (rev[mask >> 1] >> 1) ^ ((mask & 1) << (LOG - 1));
	}
}

void FFT(vector<cd> & a, int n, int LOG) {
	for (int i = 0; i < n; i++) {
		if (i < rev[i]) {
			swap(a[i], a[rev[i]]);
		}
	}
	for (int lvl = 0; lvl < LOG; lvl++) {
		int len = 1 << lvl;
		for (int st = 0; st < n; st += len << 1) {
			for (int i = 0; i < len; i++) {
				cd x = a[st + i], y = a[st + len + i] * w[i << (LOG - 1 - lvl)];
				a[st + i] = x + y;
				a[st + len + i] = x - y;
			}
		}
	}
}

vector<int> mul(vector<int> a, vector<int> b) {
	int n = a.size() + b.size();
	while (__builtin_popcount(n) != 1) {
		n++;
	}
	vector<cd> fa(n), fb(n);
	for (int i = 0; i < (int)a.size(); i++) {
		fa[i] = a[i];
	}
	for (int i = 0; i < (int)b.size(); i++) {
		fb[i] = b[i];
	}
	int LOG;
	vector<cd> w;
	vector<int> rev;
	initFFT(n, LOG);
	FFT(fa, n, LOG);
	FFT(fb, n, LOG);
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	FFT(fa, n, LOG);
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = (ll) (fa[i].real() / n + 0.5) % MOD;
	}
	reverse(ans.begin() + 1, ans.end());
	while (!ans.empty() && ans.back() == 0) ans.pop_back();
	return ans;
}

int n, m, k;
vector<int> have[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		have[i].push_back(1);
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		have[x - 1].push_back(1);
	}
	set<pair<int, int>> sz;
	for (int i = 0; i < m; i++) {
		sz.insert({have[i].size(), i});
	}
	while (sz.size() > 1) {
		int a = sz.begin()->second;
		sz.erase(sz.begin());
		int b = sz.begin()->second;
		sz.erase(sz.begin());
		have[a] = mul(have[a], have[b]);
		sz.insert({have[a].size(), a});
	}
	cout << have[sz.begin()->second][k] << endl;
	return 0;
}
