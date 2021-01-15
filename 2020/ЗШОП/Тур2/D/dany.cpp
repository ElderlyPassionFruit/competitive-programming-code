#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <complex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <bits/stdc++.h>

#define ft first
#define sc second
#define pb push_back
#define len(v) (int)v.size()
#define int ll

using namespace std;
typedef long long ll;
typedef long double ld;

int inf = 1e9 + 100;

vector<int> z(string& t, string& s) {
	string sn = t + "#" + s;
	int n = len(sn);
	vector<int> z(n + 1, 0);
	for (int i = 0, l = 0, r = 0; i < n; i++) {
		if(i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while(i + z[i] < n && sn[i + z[i]] == sn[z[i]])
			z[i]++;
		if(i + z[i] - 1 > r) 
			r = i + z[i] - 1, l = i;
	}
	vector<int> ans;
	bool flag = 0;
	for (int i = 0; i < n; i++) {
		if(sn[i] == '#') {
			flag = 1;
			continue;
		}
		if(flag)
			ans.pb(z[i]);
	}
	return ans;
}

signed main() {
	#ifdef PC
		freopen("in.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
	#endif	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int ns, nt, q;
	while(cin >> ns >> nt >> q) {
		string s, t;
		cin >> s >> t;
		string s1 = s, t1 = t;
		auto ans_sf = z(t1, s1);
		auto ans_tf = z(t1, t1);

		auto ttime = clock();
		reverse(s1.begin(), s1.end());
		reverse(t1.begin(), t1.end());
		assert((clock() - ttime) * 1.0 / CLOCKS_PER_SEC < 0.2);
		// assert(((clock() - ttime) * 1.0 / CLOCKS_PER_SEC) <= 0.5)

		auto ans_sp = z(s1, s1);
		auto ans_tp = z(s1, t1);
		ttime = clock();
		reverse(ans_sp.begin(), ans_sp.end());
		reverse(ans_tp.begin(), ans_tp.end());

		int n = len(s);
		vector<int> answ(n + 1, 0);
		for (int i = 1; i < len(s); i++) {
			int suf = ans_sf[i];
			int pref = ans_sp[i - 1];
			answ[n - pref] = max(answ[n - pref], suf);
		}
		for (int i = 1; i < len(t); i++) {
			int suf = ans_tf[i];
			int pref = ans_tp[i - 1];
			answ[n - pref] = max(answ[n - pref], suf);
		}

		for (int i = 1; i <= n; i++) {
			answ[i] = max(answ[i], answ[i - 1]);
		}
		answ[n] = inf;
		vector<int> pref(n + 1, 0);
		for (int i = 0; i < n; i++) {
			pref[i + 1] = pref[i] + answ[i];
		}
		assert((clock() - ttime) * 1.0 / CLOCKS_PER_SEC < 0.2);
		for (int i = 0; i < q; i++) {
			int ls, rs, lt, rt;
			cin >> ls >> rs >> lt >> rt;
			ls--, rs--;
			int ans = 0;
			ttime = clock();
			int l1 = lower_bound(answ.begin(), answ.end(), lt) - answ.begin();
			int r1 = lower_bound(answ.begin(), answ.end(), rt) - answ.begin();
			assert((clock() - ttime) * 1.0 / CLOCKS_PER_SEC < 0.02);

			if (l1 > rs) {
				cout << 0 << '\n';
				continue;
			}
			if(l1 < ls)
				l1 = ls;
			if(r1 < ls)
				r1 = ls;
			if(r1 > rs)
				r1 = rs + 1;

			assert(r1 <= n);
			assert(r1 >= 0);
			assert(l1 >= 0);
			assert(l1 <= n);
			ans += (pref[r1] - pref[l1]) - (r1 - l1) * (lt - 1);
			if(r1 <= rs)
				ans += (rt - lt + 1) * (rs - r1 + 1); 
			cout << ans << '\n';
		}
	}
}