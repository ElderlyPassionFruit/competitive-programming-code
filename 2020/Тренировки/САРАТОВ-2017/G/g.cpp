#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 200;
pair<int, int> a[MAXN];
int n;
ll fans;
int ans[MAXN][MAXN];

void check() {
	for (int i = 0; i < n; i++) {
		set<int> have;
		for (int j = 0; j < n; j++) {
			have.insert(ans[i][j]);
		}
		assert(have.size() == n && (*have.begin()) == 0 && (*(--have.end())) == n - 1);
	}
	for (int i = 0; i < n; i++) {
		set<int> have;
		for (int j = 0; j < n; j++) {
			have.insert(ans[j][i]);
		}
		assert(have.size() == n && (*have.begin()) == 0 && (*(--have.end())) == n - 1);
	}
	int add = 0;
	for (int i = 0; i < n; i += 2) {
		add += abs(a[i].first - a[i + 1].first);
	} 
	//cout << "add = " << add << endl;
	assert(fans == add * n);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a, a + n);
	fans = 0;
	for (int i = 0; i < n; i += 2) {
		fans += abs(a[i].first - a[i + 1].first);
	}
	fans *= n;
	for (int i = 0; i < n; i += 2) {
		for (int j = 0; j < n; j++) {
			ans[i][j] = a[(i + j) % n].second;
		}
	}
	for (int i = 0; i < n; i += 2) {
		for (int j = 0; j < n; j++) {
			ans[i + 1][j ^ 1] = ans[i][j];
		}
	} 
	cout << fans << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ans[i][j] + 1 << " ";
		}
		cout << "\n";
	}
	cout.flush();
	check();
	return 0;
}