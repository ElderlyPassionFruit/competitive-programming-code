#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
const int BUBEN = 300;
int n, q;
int x[MAXN], y[MAXN], p[MAXN];
int rp[MAXN];
pair<pair<int, int>, int> query[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i] >> p[i];
		rp[p[i]] = i;
	}	
	for (int i = 0; i < q; i++) {
		cin >> query[i].first.first >> query[i].first.second;
		query[i].second = i;
	}
	sort(query, query + q, [&] (pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
		if (a.first.first / BUBEN != b.first.first / BUBEN) return a.first.first < b.first.first;
		if (a.first.first % 2 == 0)
			return a.first.second < b.first.second;
		else
			return a.first.second > b.first.second;
	});
}

ll nxt = 0;
set<int> used;

void upd(int l, int r, int val) {
	l = rp[l];
	r = rp[r];
	nxt += val * (ll) abs(x[l] - x[r]) * abs(y[l] - y[r]);
}

void add(int pos) {
	pos = p[pos];
	auto nxt = used.lower_bound(pos);
	auto prev = nxt;
	if (nxt != used.end() && prev != used.begin()) {
		prev--;
		int P = *prev;
		int N = *nxt;
		upd(P, N, -1);
		upd(P, pos, 1);
		upd(pos, N, 1);
	} else if (nxt != used.end()) {
		int N = *nxt;
		upd(pos, N, 1);
	} else if (prev != used.begin()) {
		prev--;
		int P = *prev;
		upd(P, pos, 1);
	}
	used.insert(pos);
}

void del(int pos) {
	pos = p[pos];
	auto my = used.find(pos);
	auto nxt = my;
	nxt++;
	auto prev = my;
	if (nxt != used.end() && prev != used.begin()) {
		prev--;
		int P = *prev;
		int N = *nxt;
		upd(P, pos, -1);
		upd(pos, N, -1);
		upd(P, N, 1);	
	} else if (nxt != used.end()) {
		int N = *nxt;
		upd(pos, N, -1);
	} else if (prev != used.begin()) {
		prev--;
		int P = *prev;
		upd(P, pos, -1);
	}
	used.erase(pos);
}

ll ans[MAXN];

void run() {
	int l = 1, r = 0; 
	for (int i = 0; i < q; i++) {
		int ql = query[i].first.first, qr = query[i].first.second;
		while (ql < l) {
			l--;
			add(l);
		}		
		while (qr > r) {
			r++;
			add(r);
		}
		while (ql > l) {
			del(l);
			l++;
		}
		while (qr < r) {
			del(r);
			r--;
		}
		ans[query[i].second] = nxt;
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