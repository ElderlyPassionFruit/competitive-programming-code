#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 500010;
ll l, a, b, t, r;
int n;
ll x[MAXN];

void read() {
	cin >> l >> a >> b >> t >> r;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	x[n + 1] = l;
}

ld dp[MAXN];
int p[MAXN];

vector<int> ans;

//dp[i] = min(dp[j] + (xj - xi) / b + a * t);

void run() {
	for (int i = n; i >= 1; i--) {
		dp[i] = dp[i + 1] + (ld)(x[i + 1] - x[i]) / a;
		p[i] = p[i + 1];
		for (int j = i + 1; j <= n + 1; j++) {
			int len = x[j] - x[i];
			if (len > a * t) {
				if (len <= a * t + b * r) {
					//cout << "i = " << i << " j = " << j << " len = " << len << endl;
					//cout << a * t + b * r << endl;
					ld fans = dp[j] + t + (ld)x[j] / b - (ld)(x[i] + a * t) / b;
					//cout << fans << endl;	
					if (fans < dp[i]) {
						dp[i] = fans;
						p[i] = j;
					}
				}
				else {
					ld fans = dp[j] + r + (ld) (x[j] - b * r) / a - (ld)x[i] / a;
					cout << fans << endl;
					
					if (fans < dp[i]) {
						dp[i] = fans;
						p[i] = j;
					}
					break;
				}
			}
		}
	}

	p[0] = 1;

	cout << "dp = " << endl;
	for (int i = 0; i <= n + 1; i++)
		cout << dp[i] << " ";
	cout << endl;

	cout << "p = " << endl;
	for (int i = 0; i <= n + 1; i++)
		cout << p[i] << " ";
	cout << endl;

	int pos = 0;
	while (p[pos] != n + 1 && p[pos] != 0) {
		ans.push_back(p[pos]);
		pos = p[pos];
	}
	//assert(ans.size());
	//ans.pop_back();
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i - 1 << " ";
	cout << endl;
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