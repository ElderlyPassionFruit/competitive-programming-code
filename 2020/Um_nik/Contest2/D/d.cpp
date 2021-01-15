#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n, m;
vector<int> h, p;

bool check(int pos, int l, int r, int t) {
	if (l > r) swap(l, r);
	if (pos <= l) return r - pos <= t;
	if (pos >= r) return pos - l <= t;
	int len1 = pos - l;
	int len2 = r - pos;
	if (len1 > len2) swap(len1, len2);
	return len1 * 2 + len2 <= t;
} 

int nxt(int pos, int r, int t) {
	int L = r, R = m + 1;
	while (L < R - 1) {
		int mid = (L + R) / 2;
		int last = mid - 1;
		if (check(pos, p[r], p[last], t)) {
			L = mid;
		} else {
			R = mid;
		}
	}
	return L;
}

bool check(int t) {
	int r = 0;
	for (auto i : h) {
		r = nxt(i, r, t);
		/*int now = t;
		int pos = i;
		while (r < m && abs(pos - p[r]) <= now) {
			now -= abs(pos - p[r]);
			pos = p[r];
			r++;
		}*/
	}
	return r == m;
}

int get() {
	int l = -1, r = 1e11;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid; 
		} else {
			l = mid;
		}
	}
	return r;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	h.resize(n);
	for (auto &i : h) {
		cin >> i;
	}
	p.resize(m);
	for (auto &i : p) {
		cin >> i;
	}
	int ans;
	sort(all(h));
	sort(all(p));
	ans = get();
	reverse(all(h));
	reverse(all(p));
	ans = min(ans, get());
	cout << ans << endl;
	return 0;
}