#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace std;
typedef cc_hash_table<int, int> hash_map;

#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1791791791, b = 179, MAXN = 1e6 + 10;

int len;
char x[MAXN];
int h[MAXN], pows[MAXN];

int ans[MAXN];

void add(string & s) {
	for (int i = 0; i < s.length(); i++) {
		x[len++] = s[i];
	}
	x[len++] = '#';
}

void build() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = (long long) pows[i - 1] * b % MOD;
	}

	h[0] = 0;
	for (int i = 1; i <= len; i++) {
		h[i] = ((long long)h[i - 1] + (long long) x[i - 1] * pows[i] % MOD) % MOD;
	} 
}

int get(int l, int r) {
	return ((long long)(h[r] - h[l - 1]) + MOD) % MOD * pows[MAXN - 5 - r] % MOD;
}

int get(string & s) {
	int ans = 0;
	for (int i = 1; i <= s.length(); i++) {
		ans = ((long long)ans + (long long)s[i - 1] * pows[i] % MOD) % MOD;
	}
	return (long long)ans * pows[MAXN - 5 - s.size()] % MOD;
}

struct query {
	int hash, l, r, ind;
	query() {
		hash = 0, l = 0, r = 0, ind = 0;
	}	
	query(int a, int b, int c, int d) {
		hash = a, l = b, r = c, ind = d;
	}
};

int n, q;
map <int, vector<query> > str;

void read() {
	cin >> n >> q;
	len = 0;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add(s);
	}

	build(); 

	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		string s;
		cin >> s;
		str[s.length()].push_back({get(s), l, r, i});
	}
}

struct event{
	int x, type, hash, ind;
	event() {
		x = 0, type = 0, hash = 0, ind = 0;
	}
	event(int a, int b, int c, int d) {
		x = a, type = b, hash = c, ind = d;
	}
};

bool cmp(event a, event b) {
	return a.x < b.x;
}

void run() {
	for (auto i : str) {
		vector<event> ev;
		for (auto j : i.second) {
			ev.push_back({j.l - 1, 1, j.hash, j.ind});
			ev.push_back({j.r, 2, j.hash, j.ind});
		}

		sort(ev.begin(), ev.end(), cmp);

		hash_map help;
		int pos = 1;
		int pos_ev = 0;

		for (int j = 0; j < n; j++) {
			hash_map fhelp;
			while (pos <= len && x[pos - 1] != '#') {
				int x = get(pos, min(pos + i.first - 1, len));
				if (fhelp.find(x) == fhelp.end()) {
					help[x]++;
					fhelp[x]++;
				}
				pos++;
			}
			pos++;
			
			while (pos_ev < ev.size() && ev[pos_ev].x < j)
				pos_ev++;

			while (pos_ev < ev.size() && ev[pos_ev].x == j) {
				if (ev[pos_ev].type == 1) {
					ans[ev[pos_ev].ind] -= help[ev[pos_ev].hash];
				}
				else {
					ans[ev[pos_ev].ind] += help[ev[pos_ev].hash];				
				}
				pos_ev++;
			}
		}
	}
}

void write() {
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
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