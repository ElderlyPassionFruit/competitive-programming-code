#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e6 + 10;
int sz[MAXN], r[MAXN], pred[MAXN];

void make() {
	for (int i = 0; i < MAXN; i++) {
		sz[i] = 1;
		r[i] = i;
		pred[i] = i;
	}
}
 
int get_par(int v) {
	if (v == pred[v])
		return v;
	return pred[v] = get_par(pred[v]);
}

int get_pos(int v) {
	return r[get_par(v)];
}

void uni(int a, int b) {
	a = get_par(a), b = get_par(b);
	if (a == b)
		return;
	if (sz[a] < sz[b])
		swap(a, b);
	sz[a] += sz[b];
	pred[b] = a;
	chkmax(r[a], r[b]);
}

vector<char> ans(2e6 + 10, '0');

void add(string & s, int pos) {
	int n = s.size();
	for (int i = get_pos(pos); i < pos + n; i = get_pos(i)) {
		ans[i] = s[i - pos];
		uni(i + 1, i);
	}
}

void solve() {
	make();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string x;
		cin >> x;
		int cnt;
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			int pos;
			cin >> pos;
			pos--;
			add(x, pos);
		}
	}

	while (ans.back() == '0')
		ans.pop_back();
	for (auto &i : ans) {
		if (i != '0')
			cout << i;
		else
			cout << 'a';
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}