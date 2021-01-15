#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 1e5 + 10;

bool check(string s) {
	auto t = s;
	reverse(t.begin(), t.end());
	return s != t;
}

int n;
int cnt[MAXN];
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		cnt[s.length() * 100 + (s[0] - 'a') * 10 + (s.back() - 'a')]++;
		if (check(s))
			cnt[s.length() * 100 + (s.back() - 'a') * 10 + (s[0] - 'a')]++;
	}
}

const int MOD = 998244353;
int ans = 0;

void run() {
	for (int len = 3; len < 10; len++) {
		for (int i0 = 0; i0 < 6; i0++) {
			for (int i1 = 0; i1 < 6; i1++) {
				for (int i2 = 0; i2 < 6; i2++) {
					for (int i3 = 0; i3 < 6; i3++) {
						for (int i4 = 0; i4 < 6; i4++) {
							for (int i5 = 0; i5 < 6; i5++) {
								for (int i6 = 0; i6 < 6; i6++) {
									for (int i7 = 0; i7 < 6; i7++) {
										int fans = 1;
										
										fans *= cnt[len * 100 + i0 * 10 + i1]; 
										fans %= MOD;
										fans *= cnt[len * 100 + i0 * 10 + i3];
										fans %= MOD;
										fans *= cnt[len * 100 + i0 * 10 + i4];
										fans %= MOD;

									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void write() {
	cout << ans << endl;
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