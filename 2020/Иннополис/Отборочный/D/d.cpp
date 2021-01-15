#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

const int MAXK = 1e6 + 10;
bool used[MAXK];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int s, k;
	cin >> k >> s;
	for (int i = 0; i < MAXK; i++)
		used[i] = false;
	int now = k;
	for (int i = k - 1; i >= 0; i--) {
		if (used[i]) continue;
		for (int j = i - 1; j >= 0; j--) {
			if (used[j]) continue;
			if ((i & j) == j) continue;
			if (used[(i & j)]) continue;
			now--;
			used[(i & j)] = true;
		}
	}
	assert(now <= 125);
	vector<int> ans;
	for (int i = 0; i < k; i++) {
		if (used[i]) continue;
		ans.push_back(i);
	}
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}