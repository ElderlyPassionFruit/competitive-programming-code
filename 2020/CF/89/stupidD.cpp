#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> get(int x) {
	vector<int> ans;
	for (int i = 1; i * i <= x; i++) {
		if (x % i) continue;
		ans.push_back(i);
		if (i * i == x) continue;
		ans.push_back(x / i);
	}
	return ans;
}

const int MAXN = 1e7 + 10;
int n;
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int ans[MAXN][2];

void run() {
	for (int i = 0; i < n; i++) {
		auto x = get(a[i]);
		/*sort(all(x));
		for (auto have : x) {
			cout << have << " ";
		}
		cout << endl;*/
		bool ok = false;
		for (int j = 1; j < (int)x.size(); j++) {
			for (int k = j; k < (int)x.size(); k++) {
				if (__gcd(a[i], x[j] + x[k]) == 1) {
					ok = true;
					ans[i][0] = x[j];
					ans[i][1] = x[k];
					
					ans[i][0] = ans[i][1] = 1;
					break;
				}
			}
			if (ok) break;
		}
		if (!ok) {
			ans[i][0] = ans[i][1] = -1;
		}
	}
}

void write() {
	for (int it = 0; it < 2; it++){
		for (int i = 0; i < n; i++) {
			cout << ans[i][it] << " ";
		}
		cout << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}