#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

using cd = complex<double>;

const ld PI = acos(-1);
const int LOG = 19;
const int MAXN = (1 << LOG);

cd w[MAXN + 228];
int rev[MAXN + 228];

void initFFT() {
	for (int i = 0; i < MAXN; i++) {
		w[i] = cd(cos(2 * PI * i / MAXN), sin(2 * PI * i / MAXN));
	}
	rev[0] = 0;
	for (int mask = 1; mask < MAXN; mask++) {
		rev[mask] = (rev[mask >> 1] >> 1) ^ ((mask & 1) << (LOG - 1));
	}
}

void FFT(cd * A) {
	for (int i = 0; i < MAXN; i++) {
		if (i < rev[i]) {
			swap(A[i], A[rev[i]]);
		}
	}
	for (int l = 0; l < LOG; l++) {
		int len = 1 << l;
		for (int st = 0; st < MAXN; st += len << 1) {
			for (int i = 0; i < len; i++) {
				cd x = A[st + i], y = A[st + len + i] * w[i << (LOG - 1 - l)];
				A[st + i] = x + y;
				A[st + i + len] = x - y;
			}
		}
	}
}

int n, x;
int a[MAXN];
cd pref[MAXN], revPref[MAXN];
ll ans[MAXN];
int cnt[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cout.setf(ios::fixed);
	initFFT();
	cin >> n >> x;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i] = (a[i] >= x ? 0 : 1);
		if (i > 0) {
			a[i] += a[i - 1];
		}
		pref[a[i]] += 1;
		revPref[n - a[i]] += 1;
	}
	pref[0] += 1;
	revPref[n] += 1;

	FFT(pref);
	FFT(revPref);
	for (int i = 0; i < MAXN; i++) {
		pref[i] *= revPref[i];
	}
	FFT(pref);
	for (int i = 0; i < MAXN; i++) {
		ans[i] = (ll)(pref[i].real() / MAXN + 0.5);
	}
	reverse(ans + 1, ans + MAXN);
	for (int i = 0; i <= n; i++) {
		ans[i] = ans[i + n];
	}
	ans[0] = 0;
	cnt[0] = 1;
	for (int i = 0; i < n; i++) {
		ans[0] += cnt[a[i]];
		cnt[a[i]]++;
	}
	for (int i = 0; i <= n; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}