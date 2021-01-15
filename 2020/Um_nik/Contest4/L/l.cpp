#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

using cd = complex<double>;

const ld log3 = 0.477121254719662;
const int B = 1000;

const int MAXLOG = 21;
const int N = 1 << MAXLOG;
const int MAXN = N + 228;
const ld PI = acos(-1);
cd w[MAXN];
int rev[MAXN]; 

void initFFT() {
	for (int i = 0; i < N; i++) {
		w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
	}
	rev[0] = 0;
	for (int i = 1; i < N; i++) {
		rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (MAXLOG - 1));
	}
}

void FFT(vector<cd> & a, int n) {
	int k = 0;
	while ((1 << (k + 1)) <= n) k++;
	assert((1 << k) == n);
	for (int i = 0; i < n; i++) {
		if (i < (rev[i] >> (MAXLOG - k))) {
			swap(a[i], a[rev[i] >> (MAXLOG - k)]);
		}
	}
	for (int lvl = 0; lvl < k; lvl++) {
		int len = 1 << lvl;
		for (int st = 0; st < n; st += len << 1) {
			for (int i = 0; i < len; i++) {
				cd x = a[st + i], y = a[st + i + len] * w[i << (MAXLOG - 1 - lvl)];
				a[st + i] = x + y;
				a[st + i + len] = x - y;
			}
		}
	}
}

void mul(vector<int> & a, int x) {
	for (int i = 0; i < (int)a.size(); i++) {
		a[i] *= x;
	}
	for (int i = 0; i + 1 < (int)a.size(); i++) {
		a[i + 1] += a[i] / B;
		a[i] %= B;
	}
	while (!a.empty() && a.back() >= B) {
		a.push_back(a.back() / B);
		a[a.size() - 2] %= B;
	}
	while (!a.empty() && a.back() == 0) {
		a.pop_back();
	}
}

void mul(vector<int> & a, vector<int> & b) {
	int n = a.size() + b.size();
	while (!n || (n & (n - 1))) n++;
	vector<cd> fa(n), fb(n);
	for (int i = 0; i < (int)a.size(); i++) {
		fa[i] = a[i];
	}
	for (int i = 0; i < (int)b.size(); i++) {
		fb[i] = b[i];
	}
	FFT(fa, n);
	FFT(fb, n);
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	FFT(fa, n);
	reverse(fa.begin() + 1, fa.end());
	a.resize(n);
	for (int i = n - 1; i >= 0; i--) {
		ll x = (ll) (fa[i].real() / n + 0.5);
		a[i] = x % B;
		if (i + 1 == n) {
			assert(x / B == 0);
		} else {
			a[i + 1] += x / B;
		}
	}
	for (int i = 0; i + 1 < n; i++) {
		a[i + 1] += a[i] / B;
		a[i] %= B;
	}
	while (!a.empty() && a.back() == 0) {
		a.pop_back();
	}
}

vector<int> binpow(vector<int> & a, int n) {
	vector<int> ans = {1};
	while (n) {
		if (n & 1) {
			mul(ans, a);
		}
		mul(a, a);
		n >>= 1;
	}
	return ans;
}

bool check(vector<int> & a, vector<int> & b) {
	if (a.size() != b.size()) {
		return a.size() > b.size();
	}
	for (int i = (int)a.size() - 1; i >= 0; i--) {
		if (a[i] != b[i]) {
			return a[i] > b[i];
		}
	}
	return true;
}

string s;
vector<int> n;
vector<int> start;
int need;

void initStart() {
	need = (int)n.size() * 3 / log3;
	need -= 10;
	need = max(need, 0);
	start = {3};
	start = binpow(start, need);
}

int solve(int cnt2) {
	vector<int> now = start;
	mul(now, 1 << cnt2);
	int fans = cnt2 * 2 + need * 3;
	while (!check(now, n)) {
		mul(now, 3);
		fans += 3;
	}
	return fans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	initFFT();
	cin >> s;
	if (s == "1") {
		cout << 1 << endl;
		exit(0);
	}
	reverse(all(s));
	while (s.size() % 3 != 0) s += "0";
	reverse(all(s));
	for (int i = 0; i < (int)s.size(); i += 3) {
		n.push_back((s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 2] - '0'));
	}
	reverse(all(n));
	initStart();
	int ans = 1e9;
	for (int i = 0; i <= 2; i++) {
		ans = min(ans, solve(i));
	}
	cout << ans << endl;
	return 0;
}