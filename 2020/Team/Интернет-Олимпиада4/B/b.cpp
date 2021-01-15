#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
};

const int MAXC = 1e4 + 10;
int n;
vector<int> p[MAXC];

int m;
int r[MAXC];
pt o[MAXC];

int L[MAXC], R[MAXC];
bool used[MAXC];

int pref[MAXC];

bool check(int ind, int x, int y) {
	return (ll)(x - o[ind].x) * (x - o[ind].x) + (y - o[ind].y) * (y - o[ind].y) <= (ll) r[ind] * r[ind];
}

void recalc(int x) {
	for (int i = 0; i < m; i++) {
		if (o[i].x - r[i] == x) {
			used[i] = true;
			L[i] = o[i].y;
			R[i] = o[i].y;
			continue;
		}
		if (o[i].x + r[i] + 1 == x) {
			used[i] = false;
			continue;
		}
		if (used[i]) {
			while (check(i, x, L[i] - 1)) {L[i]--;};
			while (!check(i, x, L[i])) {L[i]++;};
			while (check(i, x, R[i] + 1)) { R[i]++;};
			while (!check(i, x, R[i])) R[i]--;
		}
	}

	for (int i = 0; i < MAXC; i++)
		pref[i] = 0;
	for (int i = 0; i < m; i++) {
		pref[max(L[i], 0)]++;
		pref[min(R[i] + 1, MAXC - 1)]--;
	}
	for (int i = 1; i < MAXC; i++)
		pref[i] += pref[i - 1];
}

int get(int x) {
	int ans = 0;
	int pos = 0;
	for (int y = 0; y < MAXC; y++) {
		while (pos < p[x].size() && p[x][pos] == y) {
			if (!pref[y])
				ans++;
			pos++;
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		p[x].push_back(y);
	}
	for (int i = 0; i < MAXC; i++) {
		sort(all(p[i]));
		p[i].resize(unique(all(p[i])) - p[i].begin());
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> o[i].x >> o[i].y >> r[i];
	}

	int ans = 0;

	for (int i = -MAXC; i < MAXC; i++) {
		recalc(i);
		ans += get(i);
	}

	cout << ans << endl;
	return 0;
}