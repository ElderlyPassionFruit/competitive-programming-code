#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll
int ans;
int k;
void relax(int n, int it) {
	while (n >= k) {
		ans = min(ans, n - k + it);
		it++;
		n /= 10;
	}
}

void gen(int n, int it) {
	for (int i = 0; i < 10 && n >= 1; i++, it++, n--) {
		relax(n, it);
	}
}


signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n >> k;
	ans = n - k;
	relax(n, 0);
	int it = 0;
	while (n) {
		gen(n, it);
		it++;
		n /= 10;
	}
	cout << ans << endl;
	return 0;
}