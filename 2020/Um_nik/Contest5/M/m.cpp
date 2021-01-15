#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
struct event{
	int type;
	int val;
	int len;
	int cnt;
	int sum;
};

vector<event> a;

int getAns(int pos) {
	int l = -1, r = (int)a.size();
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (a[mid].sum >= pos) {
			r = mid;
		} else {
			l = mid;
		}
	}
	if (a[r].type == 1) {
		return a[r].val;
	}
	return getAns((pos - (a[r].sum - a[r].len * a[r].cnt) - 1) % a[r].len + 1);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	int len = 0;
	for (int i = 0; i < n; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int x;
			cin >> x;
			len++;
			event add;
			add.type = type;
			add.sum = len;
			add.val = x;
			a.push_back(add);
		} else {
			int flen, cnt;
			cin >> flen >> cnt;
			len += flen * cnt;
			event add;
			add.type = 2;
			add.len = flen;
			add.cnt = cnt;
			add.sum = len;
			a.push_back(add); 
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int pos;
		cin >> pos;
		cout << getAns(pos) << " "; 
	}
	cout << endl;
	return 0;
}