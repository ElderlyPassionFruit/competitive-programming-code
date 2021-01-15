#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int k, cnt1, cnt2, cnt3;
int Cnt1, Cnt2, Cnt3;
void no() {
	cout << "Impossible" << endl;
	exit(0);
}

void check() {
	if (cnt3 + min(cnt1 + 1, cnt2) < k) no();
	if (cnt3 >= 2) {
		if ((cnt3 + 1) / 2 > k) no();
	} else {
		if (max(min(cnt2, 1), cnt3) > k) no();
	}
}

string ans;

void check_ans() {
	int cnt = 0;
	int last = 0;
	for (auto i : ans) {
		if (i - '0' != last && i == '1') {
			cnt++;
		}
		last = i - '0';
	}
	assert((int)ans.size() == (Cnt1 + Cnt2 + Cnt3) * 2);
	for (int i = 0; i < (int)ans.size(); i += 2) {
		if (ans[i] == ans[i + 1]) {
			if (ans[i] == '0') {
				Cnt1--;
			} else {
				Cnt2--;
			}
		} else {
			Cnt3--;
		}
	}
	assert(Cnt1 == 0 && Cnt2 == 0 && Cnt3 == 0);
	assert(k == cnt);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> k >> cnt1 >> cnt2 >> cnt3;
	Cnt1 = cnt1, Cnt2 = cnt2, Cnt3 = cnt3;
	check();
	ans = "";
	if (k >= cnt3 + (cnt2 > 0)) {
		int need = k - cnt3;
		while (cnt3 > 0) {
			ans += "10";
			cnt3--;
		}
		for (int i = 0; i < need; i++) {
			if (i > 0) ans += "00", cnt1--;
			
			assert(cnt1 >= 0);
			ans += "11";
			cnt2--;
			assert(cnt2 >= 0);
		} 
		while (cnt2 > 0) {
			ans += "11";
			cnt2--;
		}
		while (cnt1 > 0) {
			ans += "00";
			cnt1--;
		}
	} else if (k == cnt3 && cnt3 > 0) {
		while (cnt1 > 0) {
			ans += "00";
			cnt1--;
		}	
		while (cnt2 > 0) {
			ans += "11";
			cnt2--;
		}
		while (cnt3 > 0) {
			ans += "10";
			cnt3--;
		}
	} else {
		int need = k;
		if (cnt3 >= 2) {
			ans += "01";
			while (cnt2 > 0) {
				ans += "11";
				cnt2--;
			}
			ans += "10";
			cnt3 -= 2;
			need--;
		} else if (cnt3 == 1) {
			while (cnt2 > 0) {
				ans += "11";
				cnt2--;
			}
			ans += "10";
			cnt3--;
			need--;	
		} else {
			while (cnt2 > 0) {
				ans += "11";
				cnt2--;
			}
			need--;
		}
		if (cnt3 == 0) {
			assert(need == 0);
			while (cnt1 > 0) {
				ans += "00";
				cnt1--;
			}	
		} else {
			int cnt01 = cnt3 - need;
			int cnt10 = need;
			assert(cnt01 >= 0);
			assert(cnt01 <= cnt10);
			while (cnt01 > 0) {
				ans += "0110";
				cnt01--;
				cnt10--;
			}
			while (cnt10 > 0) {
				ans += "10";
				cnt10--;
			}
			while (cnt1 > 0) {
				ans += "00";
				cnt1--;
			}
		}
	}
	cout << ans << endl;
	check_ans();
	return 0;
}