#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segm{
	ll len;
	int d;
	segm() {}
	segm(ll _len, int _d) {
		len = _len, d = _d;
	}
};

void make(vector<segm> & a) {
	vector<segm> ans;
	for (auto [len, d] : a) {
		if (!len) continue;
		if (ans.empty() || ans.back().d != d) {
			ans.push_back({len, d});
		} else {
			ans[ans.size() - 1].len += len;
		}
	}
	while (!ans.empty() && ans.back().d == 0) {
		ans.pop_back();
	}
	if (ans.empty()) {
		ans.push_back({1, 0});
	}
	a = ans;
}

vector<segm> operator+(vector<segm> a, vector<segm> b) {
	ll sumA = 0;
	for (auto i : a) {
		sumA += i.len;
	}
	ll sumB = 0;
	for (auto i : b) {
		sumB += i.len;
	}
	if (sumA < sumB) {
		a.push_back({sumB - sumA, 0});
	}
	if (sumB < sumA) {
		b.push_back({sumA - sumB, 0});
	}
	vector<segm> na, nb;
	int pos = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		while (a[i].len) {
			ll add = min(a[i].len, b[pos].len);
			na.push_back({add, a[i].d});
			nb.push_back({add, b[pos].d});
			a[i].len -= add;
			b[pos].len -= add;
			if (b[pos].len) continue;
			pos++;
		}
	}
	a = na;
	b = nb;

	assert(a.size() == b.size());
	int add = 0;
	vector<segm> ans;
	
	for (int i = 0; i < (int)a.size(); i++) {
		int A = a[i].d;
		int B = b[i].d;
		assert(a[i].len == b[i].len);
		ll len = a[i].len;
		if (!len) continue;
		if (A + B + add >= 10 ) {
			if (add == 0) {
				ans.push_back({1, (A + B) % 10});
				ans.push_back({len - 1, (A + B + 1) % 10});
				add = 1;
			}
			else {
				ans.push_back({len, (A + B + 1) % 10});
				add = 1;	
			}
		}
		else {
			ans.push_back({1, A + B + add});
			ans.push_back({len - 1, A + B});
			add = 0;
		}
	}
	if (add) {
		ans.push_back({1, 1});
	}
	make(ans);
	return ans;
}

vector<segm> ReadLong() {
	int n;
	cin >> n;
	vector<segm> ans(n);
	for (auto &[len, d] :ans) {
		cin >> len >> d;
	}
	reverse(all(ans));
	return ans;
}

vector<segm> a, b;

void read() {
	a = ReadLong();
	b = ReadLong();
}

vector<segm> ans;

void run() {
	ans = a + b;
	reverse(all(ans));
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i.len << " " << i.d << endl;
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