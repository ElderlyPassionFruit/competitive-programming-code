#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
int n;
int p[MAXN];
int used[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}
	for (int i = 0; i < n; i++) {
		if (used[p[i]] == 2) continue;
		if (i + 2 < n && used[p[i + 1]] < 2 && used[p[i + 2]] == 0 && p[i + 2] > p[i + 1] && p[i + 2] > p[i]) {
			swap(p[i + 1], p[i + 2]);
			used[p[i + 1]]++;
			used[p[i + 2]]++;
			swap(p[i], p[i + 1]);
			used[p[i]]++;
			used[p[i + 1]]++;
		} else if (i + 1 < n && used[p[i + 1]] < 2 && p[i + 1] > p[i]) {
			swap(p[i], p[i + 1]);
			used[p[i]]++;
			used[p[i + 1]]++;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << p[i] + 1 << " ";
 	}
 	cout << endl;
	return 0;
}