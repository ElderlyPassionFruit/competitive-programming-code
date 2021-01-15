#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXMEM = 1e7 + 228 + 1337;

struct node{
	int l, r;
	node() {
		l = -1, r = -1;
	}
};

node tree[MAXMEM];
int topQ = 0;

void add(string s) {
	int now = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == '0' && tree[now].l == -1) {
			tree[now].l = ++topQ;
		} else if (s[i] == '1' && tree[now].r == -1) {
			tree[now].r = ++topQ;
		}
		if (s[i] == '0') {
			now = tree[now].l;
		} else {
			now = tree[now].r;
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add(s);
	}
	int ans = 0;
	for (int i = 0; i <= topQ; i++) {
		ans += (tree[i].l == -1) != (tree[i].r == -1);
	}
	cout << ans << endl;
	return 0;
}