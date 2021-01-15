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

const int N = 500001;
int a[N], b[N];

int main() {
#ifdef ONPC
	freopen("a.in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, c = 0, v, t;
	cin >> n >> t;
	vector<int> li;
	rep(i, n)
		cin >> a[i];
	if (n <= 1000) {
		for (int i = 1; i < n - 1; i++)
			li.push_back(i);
		while (1) {
			rep(i, li.size()) {
				v = li[i];
				if (a[v] > a[v - 1] && a[v] > a[v + 1])
					b[v] = max(a[v - 1], a[v + 1]);
				else if (a[v] < a[v - 1] && a[v] < a[v + 1])
					b[v] = min(a[v - 1], a[v + 1]);
				else {
					swap(li[i], li.back());
					li.pop_back();
					i--;
				}
			}
			if (li.empty())
				break;
			for (int i : li)
				a[i] = b[i];
			c++;
		}
	}
	else {
		int l = 0, r = 0;
		while (l < n - 1) {
			if (l < n - 1 && a[l] == a[l + 1]) {
				l++;
				r++;
				continue;
			}
			while (r < n - 1 && a[r] != a[r + 1])
				r++;
			c = max(c, (r - l) / 2);
			if (a[l] == a[r]) {
				for (int i = l + 1; i < r; i++)
					a[i] = a[l];
			}
			else {
				for (int i = l; i < (l + r) / 2 + 1; i++)
					a[i] = a[l];
				for (int i = (l + r) / 2 + 1; i < r; i++)
					a[i] = a[r];
			}
			l = r;
		}
	}
	cout << c << '\n';
	if (t)
		rep(i, n)
			cout << a[i] << ' ';
}

