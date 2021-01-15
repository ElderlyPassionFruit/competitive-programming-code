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
int ps[N];

int main() {
#ifdef ONPC
	freopen("a.in", "r", stdin);
#endif
	int n;
	string s;
	cin >> n >> s;
	rep(i, n)
		ps[i + 1] = ps[i] + (s[i] == '(' ? 1 : -1);
	if (ps[n] != 0) {
		cout << -1;
		return 0;
	}
	int ans = 0;
	rep(i, n) {
		if (ps[i] < 0) {
			ans++;
			if (ps[i + 1] == 0)
				ans++;
		}
	}
	cout << ans;
}

