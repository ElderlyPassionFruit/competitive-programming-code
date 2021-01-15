#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<ld> fans;
int n;
vector<int> a;

void relax(vector<int> have, ld ans) {
	vector<int> now(n);
	for (auto i : have){
		if (i == n) continue;
		now[i]++;
		if (now[i] > a[i]) return;
	}
	for (int i = 0; i < n; i++) {
		if (now[i] == a[i]) {
			fans[i] += ans;
		}
	}
}

bool check(vector<int> have) {
	vector<int> now(n);
	for (auto i : have) {
		if (i == n) continue;
		now[i]++;
		if (now[i] > a[i]) return false;
	}
	return true;
}

void gen(vector<int> have, ld ans) {
	if (have.size() == 3) {
		relax(have, ans);
		return;
	}
	have.push_back(0);
	int cnt = 0;
	for (int i = 0; i <= n; i++) {
		cnt += check(have);
		have[have.size() - 1]++;
	}
	ans /= cnt;
	have[have.size() - 1] = 0;
	for (int i = 0; i <= n; i++) {
		if (check(have)) {
			gen(have, ans);
		}
		have[have.size() - 1]++;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cout.setf(ios::fixed);
	cin >> n;
	a.resize(n);
	fans.resize(n);
	for (auto &i : a)
		cin >> i;
	gen({}, 1);
	for (auto i : fans) {
		cout << (ld)i << " ";
	}
	cout << endl;
	return 0;
}