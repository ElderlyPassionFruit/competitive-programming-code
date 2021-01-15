#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, q;
vector<char> a;

void read() {
	cin >> n >> q;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

string get(int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++)
		ans += a[i];
	return ans;
}

void run() {
	for (int i = 0; i < q; i++) {
		string type;
		cin >> type;
		if (type == "ask") {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			string fans = get(l, r);
			string ans = fans;
			reverse(all(ans));
			if (ans == fans) {
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
		else {
			int l, r;
			char x;
			cin >> l >> r >> x;
			l--;
			r--;
			for (int j = l; j <= r; j++) {
				a[j] = x;
			}
		}
	}
}

void write() {

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