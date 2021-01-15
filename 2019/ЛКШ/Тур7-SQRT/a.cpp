#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXSQ = 4000;

int n, m, sq;
vector<int> a;
vector<int> arr[MAXSQ];
vector<int> sorted[MAXSQ];
int mod[MAXSQ];

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

void build() {
	sq = sqrt(n);
	for (int i = 0; i < n; i++) {
		sorted[i / sq].push_back(a[i]);
		arr[i / sq].push_back(a[i]);
	}

	for (int i = 0; i <= sq; i++)
		sort(sorted[i].begin(), sorted[i].end());
}

void add(int pos, int x) {
	arr[pos / sq][pos % sq] += x;
}

void fsort(int pos) {
	if (pos >= 0 && pos < n){
		sorted[pos / sq] = arr[pos / sq];
		sort(sorted[pos / sq].begin(), sorted[pos / sq].end());
	}
}

void add(int l, int r, int x) {
	while (l % sq != 0 && l < r) {
		add(l, x);
		l++;
	}

	fsort(l - 1);

	while (r % sq != 0 && l < r) {
		r--;
		add(r, x);
	}

	fsort(r);

	for (int i = l / sq; i < r / sq; i++) {
		mod[i] += x;
	}
}

bool get(int pos, int x) {
	int have = arr[pos / sq][pos % sq] + mod[pos / sq];
	return have == x;
}

bool get(int l, int r, int x) {
	while (l % sq != 0 && l < r) {
		if (get(l, x))
			return true;
		l++;
	}

	while (r % sq != 0 && l < r) {
		r--;
		if (get(r, x))
			return true;
	}

	for (int i = l / sq; i < r / sq; i++) {
		auto it = lower_bound(sorted[i].begin(), sorted[i].end(), x - mod[i]);
		if (it == sorted[i].end()) continue;
		if ((*it) == x - mod[i])
			return true;
	}
	return false;
}

vector<bool> ans;

void run() {
	build();
	for (int i = 0; i < m; i++) { 
		char type;
		cin >> type;
		if (type == '+') {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			add(l, r, x);
		}
		if (type == '?') {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			ans.push_back(get(l, r, x));
		}
	}
}

void write() {
	for (auto i : ans) {
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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