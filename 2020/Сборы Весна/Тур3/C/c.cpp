#pragma GCC optimize("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,avx256,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

namespace solver1{
	int n, k, m;
	string s;

	int add(int a, int b) {
		a += b;
		if (a >= m)
			a -= m;
		return a;
	}

	int sub(int a, int b) {
		a -= b;
		if (a < 0)
			a += m;
		return a;
	}

	int mul(int a, int b) {
		return a * b % m;
	}

	void init(int _n, int _k, int _m, string _s) {
		n = _n, k = _k, m = _m, s = _s;
	}

	const int MAXN = 201;
	const int MAXM = 1001;

	int pows[MAXN], pref[MAXN];


	int get_num(char x) {
		return (x - '0') % m;
	}

	int get_num(int l, int r) {
		l++;
		r++;
		return sub(pref[r], mul(pref[l - 1], pows[r - l + 1]));
	}

	void precalc() {
		pows[0] = 1;
		pref[0] = 0;
		for (int i = 1; i <= n; i++) {
			pows[i] = mul(pows[i - 1], 10);
			pref[i] = add(mul(pref[i - 1], 10), get_num(s[i - 1]));
		}
	}

	bitset<MAXM> can[MAXN][MAXN];

	void build_can() {
		for (int l = 0; l < n; l++) {
			for (int r = 0; r < n; r++) {
				can[l][r] &= 0;
				can[l][r][get_num(l, r)] = 1;
			}
			can[l][l][get_num(s[l])] = 1;
		}

		for (int l = n - 1; l >= 0; l--) {
			for (int mid = l; mid < n; mid++) {
				int valL = get_num(l, mid);
				for (int r = mid + 1; r < n; r++) {
					can[l][r] |= (can[mid + 1][r] << valL);
					can[l][r] |= (can[mid + 1][r] >> (m - valL));
				}
			}
		}
	}
    
	bitset<MAXM> dp[MAXN][MAXN];

	void calc_dp() {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= k + 1; j++) {
				dp[i][j] &= 0;
			}
		}
		for (int i = 0; i < m; i++) {
			dp[0][0][i] = 1;
		}

		for (int last = 0; last < n; last++) {
			for (int i = last + 1; i <= n; i++) {
				for (int cnt = 0; cnt <= k; cnt++) {
					dp[i][cnt + 1] |= dp[last][cnt] & can[last][i - 1];
				}
			}
		}
	}

	string gen(int l, int r, int val) {
		assert(can[l][r][val]);
		string ans = "";
		int pos = -1;
		for (int i = l; i < r; i++) {
			int valL = get_num(l, i);
			int valR = sub(val, valL);
			if (!can[i + 1][r][valR]) continue;
			pos = i;
			break;
		}
		if (pos == -1) {
			for (int i = l; i <= r; i++) {
				ans += s[i];
			}
			return ans;
		}
		int valL = get_num(l, pos);
		int valR = sub(val, valL);
		ans += gen(l, pos, valL);
		ans += "+";	
		ans += gen(pos + 1, r, valR);
		return ans;
	}

	void make_ans() {
		for (int val = 0; val < m; val++) {
			if (!dp[n][k + 1][val]) continue;
			vector<string> ans;

			int pos = n;
			int cnt = k + 1;

			while (pos > 0) {
				int last = -1;
				for (int i = 0; i < pos; i++) {
					if (!can[i][pos - 1][val]) continue;
					if (!dp[i][cnt - 1][val]) continue;
					last = i;
					break;
				}
				ans.push_back(gen(last, pos - 1, val));
				pos = last;
				cnt--;
			}
			assert(cnt == 0);
			reverse(all(ans));
			for (int i = 0; i < (int)ans.size(); i++) {
				cout << ans[i];
				if (i != (int)ans.size() - 1)
					cout << "=";
			}
			cout << "\n";
			return;
		}
		cout << "Fail" << "\n";
	}

	void solve() {
		precalc();
		build_can();
		calc_dp();
		make_ans();
	}
};

namespace solver2{
	int n, k, m;
	string s;

	int add(int a, int b) {
		a += b;
		if (a >= m)
			a -= m;
		return a;
	}

	int sub(int a, int b) {
		a -= b;
		if (a < 0)
			a += m;
		return a;
	}

	int mul(int a, int b) {
		return a * b % m;
	}

	void init(int _n, int _k, int _m, string _s) {
		n = _n, k = _k, m = _m, s = _s;
	}

	const int MAXN = 110;
	const int MAXM = 1010;
	int pows[MAXN], pref[MAXN];


	int get_num(char x) {
		return (x - '0') % m;
	}

	int get_num(int l, int r) {
		l++;
		r++;
		return sub(pref[r], mul(pref[l - 1], pows[r - l + 1]));
	}

	void precalc() {
		pows[0] = 1;
		pref[0] = 0;
		for (int i = 1; i <= n; i++) {
			pows[i] = mul(pows[i - 1], 10);
			pref[i] = add(mul(pref[i - 1], 10), get_num(s[i - 1]));
		}
	}

	bitset<MAXM> can[2][MAXN][MAXN];
	
	void build_can() {
		for (int type = 0; type < 2; type++) {
			for (int l = 0; l < n; l++) {
				for (int r = 0; r < n; r++) {
					can[type][l][r] &= 0;
					if (r >= l) {
						can[1][l][r][get_num(l, r)] = 1;
					}
				}
			}
		}

		for (int l = n - 1; l >= 0; l--) {
			for (int r = l; r < n; r++) {
				for (int mid = l; mid < r; mid++) {
					int valL = get_num(l, mid);
					if (!can[1][l][mid][valL]) continue;
					for (int valR = 0; valR < m; valR++) {
						if (!can[1][mid + 1][r][valR]) continue;
						int val = mul(valL, valR);
						can[1][l][r][val] = 1;
					}
				}
			}
		}

		for (int r = 0; r < n; r++) {
			for (int l = r - 1; l >= 0; l--) {
				// add +
				for (int val = 0; val < m; val++) {
					for (int mid = l; mid < r; mid++) {
						bool flag = false;
						for (int valL = 0; valL < m; valL++) {
							int valR = sub(val, valL);
							assert(valR >= 0 && valR < m);
							if (!can[0][l][mid][valL] && !can[1][l][mid][valL]) continue;
							if (!can[0][mid + 1][r][valR] && !can[1][mid + 1][r][valR]) continue;
							can[0][l][r][val] = 1;
							
							flag = true;
							break;
						}
						if (flag) break;
					}
				}
			}
		}
	}

	bitset<MAXM> dp[MAXN][MAXN];

	void calc_dp() {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= k + 1; j++) {
				dp[i][j] &= 0;
			}
		}
		for (int i = 0; i < m; i++) {
			dp[0][0][i] = 1;
		}

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= k + 1; j++) {
				dp[i][j] &= 0;
			}
		}
		for (int i = 0; i < m; i++) {
			dp[0][0][i] = 1;
		}

		for (int last = 0; last < n; last++) {
			for (int i = last + 1; i <= n; i++) {
				for (int cnt = 0; cnt <= k; cnt++) {
					dp[i][cnt + 1] |= dp[last][cnt] & can[0][last][i - 1];
					dp[i][cnt + 1] |= dp[last][cnt] & can[1][last][i - 1];
				}
			}
		}
	}

	string gen(int l, int r, int val) {
		string ans = "";
		bool type = can[1][l][r][val];
		if (type == 0) {
			for (int pos = l; pos < r; pos++) {
				for (int valL = 0; valL < m; valL++) {
					if (!can[0][l][pos][valL] && !can[1][l][pos][valL]) continue;
					int valR = sub(val, valL);
					if (!can[0][pos + 1][r][valR] && !can[1][pos + 1][r][valR]) continue;
					ans += gen(l, pos, valL);
					ans += "+";
					ans += gen(pos + 1, r, valR);
					return ans;
				}
			}
		} else {
			for (int pos = l; pos < r; pos++) {
				for (int valL = 0; valL < m; valL++) {
					if (!can[1][l][pos][valL]) continue;
					for (int valR = 0; valR < m; valR++) {
						if (!can[1][pos + 1][r][valR]) continue;
						if (mul(valL, valR) != val) continue;
						ans += gen(l, pos, valL);
						ans += "*";
						ans += gen(pos + 1, r, valR);
						return ans;
					}
				}
			}
		}
		for (int i = l; i <= r; i++) {
			ans += s[i];
		}
		return ans;
	}

	void make_ans() {
		for (int val = 0; val < m; val++) {
			if (dp[n][k + 1][val] == 0) continue;
			vector<string> ans;

			int pos = n;
			int cnt = k + 1;

			while (pos > 0) {
				int last = -1;
				for (int i = 0; i < pos; i++) {
					if (!can[0][i][pos - 1][val] && !can[1][i][pos - 1][val]) continue;
					if (dp[i][cnt - 1][val] == 0) continue;
					last = i;
					break;
				}
				ans.push_back(gen(last, pos - 1, val));
				pos = last;
				cnt--;
			}
			assert(cnt == 0);
			reverse(all(ans));
			for (int i = 0; i < (int)ans.size(); i++) {
				cout << ans[i];
				if (i != (int)ans.size() - 1)
					cout << "=";
			}
			cout << "\n";
			return;
		}
		cout << "Fail" << "\n";
	}

	void solve() {
		precalc();
		build_can();
		calc_dp();
		make_ans();
	}
};

int n, k, m, t;
string s;

void solve() {
	cin >> n >> k >> m >> t >> s;
	if (t == 1) {
		solver1::init(n, k, m, s);
		solver1::solve();
	} else {
		solver2::init(n, k, m, s);
		solver2::solve();
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}