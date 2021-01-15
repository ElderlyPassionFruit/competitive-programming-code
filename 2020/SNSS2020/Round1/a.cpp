#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct segm{
	int l, r;
};

int n;
vector<segm> a, b;

void read() {
	cin >> n;
	a.resize(n), b.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].l >> b[i].l >> a[i].r >> b[i].r;
		if (a[i].l > a[i].r) swap(a[i].l, a[i].r);
		if (b[i].l > b[i].r) swap(b[i].l, b[i].r);
	}
}

struct SegmentTree{
	int n;
	vector<int> tree;
	SegmentTree() {}
	SegmentTree(int _n) {
		n = _n;
		tree.assign(n, 0);
	}

	void upd(int l, int r, int x) {
		tree[l] += x;
		if (r + 1 < n) tree[r + 1] -= x; 
	}

	void relax() {
		for (int i = 1; i < n; i++) {
			tree[i] += tree[i - 1];
		}
	}

	int get(int pos) {
		if (pos < 0 || pos >= n) return 0;
		return tree[pos];
	}
};

vector<int> coord;

void buildCoord(vector<segm> & a) {
	coord.clear();
	for (auto i : a) {
		coord.push_back(i.l);
		coord.push_back(i.r);
		coord.push_back((i.l + i.r) / 2);
		coord.push_back((i.l + i.r) / 2 + 1);
	}
	sort(all(coord));
	coord.resize(unique(all(coord)) - coord.begin());
}

int getCoord(int x) {
	return lower_bound(all(coord), x) - coord.begin();
}

int solve(vector<segm> & a) {
	buildCoord(a);
	SegmentTree L(coord.size()), R(coord.size());
	SegmentTree cntL(coord.size()), cntR(coord.size());
	for (auto [l, r] : a) {
		int midL = (r + l) / 2;
		int midR = midL + 1;
		R.upd(0, getCoord(l), l);
		cntR.upd(0, getCoord(l), 1);
		L.upd(getCoord(l), getCoord(midL), l);
		cntL.upd(getCoord(l), getCoord(midL), 1);
		R.upd(getCoord(midR), getCoord(r), r);
		cntR.upd(getCoord(midR), getCoord(r), 1);
		L.upd(getCoord(r), (int)coord.size() - 1, r);	
		cntL.upd(getCoord(r), (int)coord.size() - 1, 1);
	}
	int ans = 1e18;

	cntL.relax();
	L.relax();
	cntR.relax();
	R.relax();

	for (int i = 0; i < (int)coord.size(); i++) {
		int fans = 0;
		int cntl = cntL.get(i);
		int suml = L.get(i);
		int cntr = cntR.get(i);
		int sumr = R.get(i);
		fans += cntl * coord[i] - suml;
		fans += sumr - cntr * coord[i];
		chkmin(ans, fans);
	}
	return ans;
}

int ans;

void run() {
	ans = solve(a) + solve(b);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}