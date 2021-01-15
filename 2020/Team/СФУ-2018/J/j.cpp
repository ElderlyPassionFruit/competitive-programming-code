#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define all(a) (a).begin(), (a).end()
#define pii pair <int, int>
const ll inf = 4e15;

ll mul(ll a, ll b) {
    if (a > (inf + b - 1) / b) return inf;
    return a * b;
}

ll best_x = inf;


ll x;
int l;

void solve(ll b) {
	vector<int> v;
	ll x1 = x;

	while (x1) {
		v.push_back(x1 % b);
		x1 /= b;
	}
	int n = v.size();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += (v[i] == 0);
		if (v[i] != 0) break;
	}

	if (cnt >= l) {
		// for (auto i : v) {
		// 	cout << i;
		// } cout << '\n';
		best_x = x;
		return;
	}

	if (l >= n) {
		x1 = 1;
		for (int i = 0; i < l; i++) {
			x1 = mul(x1, b);
			if (x1 >= best_x) {
				return;
			}
		}
		best_x = min(best_x, x1);
		return;
	}

	ll del = 0;
	ll pwr = 1;

	for (int i = 0; i < n - 1; i++) {
		if (v[i] == 0) {
			pwr *= b;
			continue;
		}

		del += mul((b - v[i]), pwr);
		cnt++;
		
		v[i + 1]++;
		if (cnt == l) {
			if (x + del == 9991) {
				cout << b << '\n';
			}
			best_x = min(best_x, x + del);

			return;
		}
		pwr *= b;
	}
	return;
}

void ansver() {
	cout << best_x << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> x >> l;

	x++;

	if (l == 1) {
		// кажется это правда
		cout << x;
		return 0;
	}

	int sqrx = round(sqrt(x));

	sqrx += 100;

	for (int b = 2; b <= sqrx; b++) {
		solve(b);
	}

	ansver();
	return 0;
}