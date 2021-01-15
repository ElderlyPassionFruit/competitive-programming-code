#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r, ind;
	segment() {}
	segment(int _l, int _r, int _ind) {
		l = _l, r = _r, ind = _ind;
	}
};

int n;
vector<int> l;

void read() {
	cin >> n;
	l.resize(n);
	for (auto &i : l) {
		cin >> i;
	}
}

vector<segment> have;

void init() {
	have.clear();
	have.push_back({0, l[0], 0});
}

void relax() {
	while (have.size() >= 2) {
		auto R = have.back();
		have.pop_back();
		auto L = have.back();
		have.pop_back();
		assert(L.r == R.l);
		if (R.ind != L.ind) {
			have.push_back(L);
			have.push_back(R);
			break;
		}
		L.r = R.r;
		have.push_back(L);
	}
}

int ans = 0;

void make(int len) {
	auto last = have.back();
	have.pop_back();
	if (last.r < len) {
		have.push_back(last);
		have.push_back({last.r, len, 0});
		relax();
		return;
	}
	have.push_back(last);

	while (true) {
		auto last = have.back();
		have.pop_back();
		if (last.l >= len) continue;
		chkmin(last.r, len);
		have.push_back(last);
		break;	
	}

	if (have.size() == 1) {
		auto last = have.back();
		have.pop_back();
		last.r--;
		if (last.l != last.r) {
			have.push_back(last);
		}
		have.push_back({last.r, last.r + 1, last.ind + 1});
	}
	else {
		auto R = have.back();
		have.pop_back();
		if (R.ind < ans) {
			R.r--;
			if (R.l != R.r) {
				have.push_back(R);
			}
			have.push_back({R.r, R.r + 1, R.ind + 1});
			relax();
		}
		else {
			auto L = have.back();
			have.pop_back();
			L.r--;
			if (L.l != L.r) {
				have.push_back(L);
			}
			have.push_back({L.r, L.r + 1, L.ind + 1});
			relax();
			have.push_back({R.l, R.r, 0});
		}
	}
	relax();
}

bool check(int fans) {
	init();
	ans = fans;
	for (int i = 1; i < n; i++) {
		make(l[i]);
	}

	for (auto i : have)
		if (i.ind > fans)
			return false;
	return true;
}

void run() {
	int l = -1, r = 1e5 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) 
			r = mid;
		else
			l = mid;
	}
	ans = r + 1;
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