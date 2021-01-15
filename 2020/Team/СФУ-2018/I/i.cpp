#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct segm{
	int val, len;
	segm() {}
	segm(int _val, int _len) {
		val = _val, len = _len;
	}
};

void relax(vector<segm> & a) {
	vector<segm> ans;
	for (auto [val, len] : a) {
		if (len == 0) continue;
		if (ans.empty() || ans.back().val != val) {
			ans.push_back({val, len});
		} else {
			ans[ans.size() - 1].len += len;
		}
	}
	while (!ans.empty() && ans.back().val == 0) {
		ans.pop_back();
	}
	a = ans;
}

vector<segm> operator+(vector<segm> a, vector<segm> b) {
	reverse(all(a));
	reverse(all(b));
	int sumA = 0, sumB = 0;
	for (auto i : a)
		sumA += i.len;
	for (auto i : b)
		sumB += i.len;
	
	if (sumA > sumB) {
		b.push_back({0, sumA - sumB});
	} else if (sumB > sumA) {
		a.push_back({0, sumB - sumA});
	}

	vector<segm> na, nb;
	int posA = 0, posB = 0;
	while (posA < a.size() && posB < b.size()) {
		int add = min(a[posA].len, b[posB].len);
		na.push_back({a[posA].val, add});
		nb.push_back({b[posB].val, add});
		a[posA].len -= add;
		b[posB].len -= add;
		if (a[posA].len == 0) posA++;
		if (b[posB].len == 0) posB++;
	}

	assert(posA == a.size());
	assert(posB == b.size());

	a = na;
	b = nb;

	vector<segm> ans;
	int add = 0;
	for (int i = 0; i < (int) a.size(); i++) {
		if (a[i].val + b[i].val + add < 2) {
			if (add == 0) {
				ans.push_back({a[i].val + b[i].val, a[i].len});
			} else {
				ans.push_back({1, 1});
				if (a[i].len > 1) {
					ans.push_back({0, a[i].len - 1});
				}
			}
			add = 0;
		} else {
			if (add == 0) {
				ans.push_back({0, 1});
				ans.push_back({1, a[i].len - 1});
			} else {
				if (a[i].val + b[i].val == 2) {
					ans.push_back({1, a[i].len});
				} else {
					ans.push_back({0, a[i].len});
				}
			}
			add = 1;
		}
	}

	if (add) {
		ans.push_back({1, 1});
	}
	relax(ans);
	reverse(all(ans));
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	vector<segm> a;
	a.resize(4);
	for (int i = 0; i < 4; i++) {
		cin >> a[i].len;
		a[i].val = 1 - i % 2;
	} 
	vector<segm> b;
	b.resize(4);
	for (int i = 0; i < 4; i++) {
		cin >> b[i].len;
		b[i].val = 1 - i % 2;
	} 
	
	auto fans = a + b;
	for (auto i : fans) {
		cout << i.len << " ";
	}
	cout << endl;
	return 0;
}