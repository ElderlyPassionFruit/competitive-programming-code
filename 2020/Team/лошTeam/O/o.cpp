



#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

vector<int> dx, dy;
vector<int> ans;

void add2(int L, int R, int x) {
	if (R < L) return;
	if (L < ans.size()) ans[L] += x;
	if (R + 1 < ans.size()) ans[R + 1] -= x;
}

void add(int L, int R, int x, int y) {
	if (R < L) return;
	add2(L + 1, R, y);
	add2(L, L, x);
	add2(R + 1, R + 1, -x - y * (R - L));
	/*for (int i = L; i <= R; i++) {
		ans[i] += x;
		x += y;
	}*/
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}

	vector<int> pos(n + 1);
	for (int i = 1; i <= n; i++) {
		pos[p[i]] = i;
	}

	ans.resize(n);

	for (int x = 1; x <= n; x++) {
		if (pos[x] <= x) {
			add(x - pos[x], n - pos[x], 0, 1);
			add(0, x - pos[x], x - pos[x], -1);
			add(n - pos[x] + 1, n - 1, x - 1, -1);
		} else {
			add(0, n - pos[x], pos[x] - x, 1);
			add(n - pos[x] + 1, n - pos[x] + x, x - 1, -1);
			add(n - pos[x] + x + 1, n - 1, 1, 1); //(начало, конец, начальный член, знаменатель)
			//pos индексируй с единицы
		}
	}
	/*
	cout << "ans = " << endl;
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;*/

	for (int i = 1; i < n; i++) {
		ans[i] += ans[i - 1];
	}
	for (int i = 1; i < n; i++) {
		ans[i] += ans[i - 1];
	}
	/*for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;*/
	int fans = min_element(all(ans)) - ans.begin();
	cout << ans[fans] << " " << fans << endl;
	return 0;
}