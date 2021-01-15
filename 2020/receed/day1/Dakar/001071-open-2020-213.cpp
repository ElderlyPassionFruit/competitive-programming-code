#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

using ll = long long;
using ld = long double;
using ul = unsigned long long;
using namespace std;
using namespace __gnu_pbds;

const int N = 1000001;
char s[N];
int p[N], f[N];

void add(int v, int d) {
	for (int i = v; i < N; i |= (i + 1))
		f[i] += d;
}

int sum(int v) {
	int r = 0;
	for (int i = v; i; i &= (i - 1))
		r += f[i - 1];
	return r;
}
int sum(int l, int r) {
	return sum(r) - sum(l);
}

int main() {
#ifdef ONPC
	freopen("a.in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, l = 0, r = 0;
	cin >> n >> s;
	rep(i, 2 * n - 1) {
		if ((l + r) * 2 - i >= 0)
			p[i] = min(p[(l + r) * 2 - i], r * 2 - i + 1);
		p[i] = max(p[i], 1 - i % 2);
		while ((i - p[i] - 1) / 2 >= 0 && (i + p[i] + 1) / 2 < n && s[(i - p[i] - 1) / 2] == s[(i + p[i] + 1) / 2])
			p[i] += 2;
		if ((i + p[i] - 1) / 2 > r) {
			l = (i - p[i] + 1) / 2;
			r = (i + p[i] - 1) / 2;
		}
	}
	ll ans = 0;
	rep(z, 2) {
		memset(f, 0, N * sizeof(int));
		set<pair<int, int>> s;
		for (int i = z * 2 + 1; i < 2 * n - 1; i += 4) {
			while (!s.empty() && (*s.begin()).first < i) {
				add((*s.begin()).second, -1);
				s.erase(s.begin());
			}
			ans += sum(max(i - p[i] * 2, 0), i);
			add(i, 1);
			s.insert({2 * p[i] + i, i});
		}
	}
	rep(z, 2) {
		memset(f, 0, N * sizeof(int));
		set<pair<int, int>> s;
		for (int i = 0; i < 2 * n - 1; i += 2) {
			if (i / 2 % 2 == z) {
				while (!s.empty() && (*s.begin()).first < i) {
					add((*s.begin()).second, -1);
					s.erase(s.begin());
				}
				ans += sum(max(i - p[i] * 2, 0), i);
			}
			else {
				add(i, 1);
				s.insert({2 * p[i] + i, i});
			}
		}
	}
	cout << ans;
}

