#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

vector<int> ans;

void run() {
	int q;
	cin >> q;
	while (q--) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int l, r, y1, y2;
			cin >> l >> y1 >> r >> y2;
			l--;
			r--;
			int ans1 = 0;
			int ans2 = 0;
			for (int i = l; i <= r; i++) {
				if (a[i] < (y1 + y2 + 1) / 2) ans1++;
				if (a[i] > (y1 + y2) / 2) ans2++;
			}
			//cout << ans1 << " " << ans2 << endl;
			if (ans1 == ans2) ans.push_back(0);
			if (ans1 > ans2) ans.push_back(1);
			if (ans1 < ans2) ans.push_back(2);
		}
		else {
			int pos, val;
			cin >> pos >> val;
			pos--;
			a[pos] = val;
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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