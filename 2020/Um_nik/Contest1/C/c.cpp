#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

const int MAXMEM = 1e7 + 10;

int lp[MAXMEM];
vector<int> p;
void genP() {
	for (int i = 2; i < MAXMEM; i++) {
		if (!lp[i]) {
			lp[i] = i;
			p.push_back(i);
		}
		for (int j = 0; j < (int)p.size() && p[j] * i < MAXMEM && p[j] <= lp[i]; j++) {
			lp[i * p[j]] = p[j];
		}
	}
	/*cout << "p = " << endl;
	for (int i = 0; i < 10; i++) {
		cout << p[i] << " ";
	}
	cout << endl;*/
}

int n;
int cnt[MAXMEM];
int cntPrimes[MAXMEM];

void buildCnt() {
	for (int i = MAXMEM - 2; i >= 0; i--) {
		cnt[i] += cnt[i + 1];
	}
	/*cout << "cnt = " << endl;
	for (int i = 0; i < MAXMEM; i++) {
		if (cnt[i]) {
			cout << i << " " << cnt[i] << endl;
		}
	}
	cout << endl;*/
	for (auto x : p) {
		for (int j = x; j < MAXMEM; j += x) {
			int now = j;
			while (now % x == 0) {
				cntPrimes[x] += cnt[j];
				now /= x;
			}
		}
	}	
	/*cout << "cntPrimes = " << endl;
	for (int i = 0; i < MAXMEM; i++) {
		if (cntPrimes[i]) {
			cout << i << " " << cntPrimes[i] << endl;
		}
	}*/
}

int stupidCalc(int now, int x) {
	int ans = 0;
	for (int i = 1; i <= now; i++) {
		int fans = i;
		while (fans % x == 0) {
			ans++;
			fans /= x;
		}
	}
	return ans;
}

bool check(int have) {
	for (auto x : p) {
		if (!cntPrimes[x]) continue;
		int now = have;
		int cnt = 0;
		while (now >= x) {
			cnt += now / x;
			now /= x;
		}
		//cnt = stupidCalc(have, x);
		//cout << x << " " << cnt << endl;
		if (cntPrimes[x] > cnt) {
			return false;
		}
	}
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	genP();
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	buildCnt();
	int l = 0, r = 1e13 + 228;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}