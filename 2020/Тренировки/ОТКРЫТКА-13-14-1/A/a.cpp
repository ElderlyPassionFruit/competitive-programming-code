#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define int ll
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
}

struct event{
	int k, ind;
	event() {}
	event(int _k, int _ind) {
		k = _k, ind = _ind;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.k, a.ind) < tie(b.k, b.ind);
}

vector<pair<int, int>> ans;

void run() {
	int q;
	cin >> q;
	vector<event> have(q);
	for (int i = 0; i < q; i++) {
		cin >> have[i].k;
		have[i].ind = i;
	}
	sort(all(have));
	queue<int> fa;
	int now1 = a[0], now2 = a[1];
	for (int i = 2; i < n; i++) {
		fa.push(a[i]);
	}
	int it = 1;
	int pos = 0;
	ans.resize(q);
	while (now1 != n && now2 != n) {
		while (pos < have.size() && have[pos].k == it) {
			ans[have[pos].ind] = {now1, now2};
			pos++;
		}
		int v = fa.front();
		fa.pop();
		if (now1 < now2) {
			swap(now1, now2);
		}
		fa.push(now2);
		now2 = v;
		it++;
	}
	if (now1 < now2) swap(now1, now2);
	a.clear();
	a.push_back(now2);
	while (!fa.empty()) {
		a.push_back(fa.front());
		fa.pop();
	}
	for (int i = pos; i < have.size(); i++) {
		have[i].k -= it;
		have[i].k %= (n - 1);
		ans[have[i].ind] = {n, a[have[i].k]};
	}
}

void write() {
	for (auto i : ans) {
		cout << i.first << " " << i.second << "\n";
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