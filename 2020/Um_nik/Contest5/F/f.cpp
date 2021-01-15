#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int len, n;
vector<int> have[2];

ll ans = 0;
int lenAns = 0;

void relax(ll cnt, int myLen) {
	assert(cnt >= 0);
	if (!cnt) return;
	if (lenAns > myLen) return;
	if (lenAns < myLen) {
		ans = 0;
	}
	lenAns = myLen;
	ans += cnt;
}

int get(int L, int R, vector<int> & have) {
	if (L > R) return 0;
	return upper_bound(all(have), R) - lower_bound(all(have), L);
}

void solveAllSame() {
	vector<int> & a = have[0];
	if (a.empty()) return;
	sort(all(a));
	auto have = a;
	have.resize(unique(all(have)) - have.begin());
	int n = have.size();
	for (int i = 0; i < n; i++) {
		int cnt = get(have[i], have[i], a);
		relax((ll)cnt * (cnt - 1) * (cnt - 2) / 6, 0);
	}	
}

void solveSame() {
	vector<int> & a = have[0];
	if (a.empty()) return;
	sort(all(a));
	if (a[0] == a.back()) return;
	int cntL = get(a[0], a[0], a);
	int cntR = get(a.back(), a.back(), a);
	int val = a.back() - a[0];
	relax((ll)cntL * (cntL - 1) / 2 * cntR + (ll)cntL * cntR * (cntR - 1) / 2, val);
	relax((ll)(n - cntL - cntR) * cntL * cntR, val);
}

void solveMid() {
	vector<int> & a = have[0];
	vector<int> & b = have[1];
	if (a.size() < 2) return;
	if (b.empty()) return;
	sort(all(a));
	sort(all(b));
	int m = b.size();
	for (int i = 0; i < m; i++) {
		int cntL = get(0, b[i] - 1, a);
		int cntR = get(b[i] + 1, len, a);
		int cntMy = get(b[i], b[i], a);
		relax((ll)cntL * cntR + (ll)cntL * cntMy + (ll)cntR * cntMy + (ll)cntMy * (cntMy - 1) / 2, len);
	}
}

void solveDiff() {
	vector<int> & a = have[0];
	vector<int> & b = have[1];
	if (a.size() < 2) return;
	if (b.empty()) return;
	sort(all(a));
	sort(all(b));
	int n = a.size(), m = b.size();
	for (int i = 0; i < m; i++) {
		int posUpper = upper_bound(all(a), b[i]) - a.begin();
		if (posUpper == n) continue;
		int cntMy = get(a[posUpper], a[posUpper], a);
		int cntMore = (posUpper != n - 1 ? get(a[posUpper] + 1, len, a) : 0);
		relax((ll)cntMy * cntMore + (ll)cntMy * (cntMy - 1) / 2, len - (a[posUpper] - b[i]));
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> len >> n;
	for (int i = 0; i < n; i++) {
		int s, f;
		cin >> s >> f;
		have[s].push_back(f);
	}
	for (int i = 0; i < 2; i++) {
		solveAllSame();
		solveSame();
		solveMid();
		for (int j = 0; j < 2; j++) {
			solveDiff();
			for (int pos = 0; pos < 2; pos++) {
				for (auto &x : have[pos]) {
					x = len - x;
				}
			}
		}
		swap(have[0], have[1]);
	}
	cout << ans << endl;
	return 0;
}

/*
WA 143
input = 
4 4
1 2
1 3
1 1
1 3

ans =  3

out =  2
*/