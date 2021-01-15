#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, m;
vector<pair <int, int>> a, b;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		l--;
		r--;
		if (t == 0)
			a.push_back({l, r});
		else
			b.push_back({l, r});
	}
}

vector<int> ans;

void run() {
	for (auto &i : a) {
		for (auto j : b) {
			if (i.first >= j.second || i.second <= j.first) continue;
			if (i.first >= j.first && i.second <= j.second) {
				cout << "NO\n";
				exit(0);
			}
			if (i.first >= j.first) {
				chkmax(i.first, j.second);
			}
			else {
				chkmin(i.second, j.first);
			}
		}
	}

/*	cout << "a = " << endl;
	for (auto i : a) cout << i.first << " " << i.second << endl;
	cout << "b = " << endl;
	for (auto i : b) cout << i.first << " " << i.second << endl;
*/	ans.assign(n, 1);

	for (auto i : a) {
		for (int j = i.second - 1; j >= i.first; j--) {
			ans[j] = ans[j + 1] + 1;
		}
	}
	
	for (auto i : b) {
		int cnt = 1;
		for (int j = i.first + 1; j <= i.second; j++) {
			ans[j] = ans[j - 1] + 1;
		}
	}
	
/*	cout << "ans = " << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
*/

}

void write() {
	cout << "YES\n";
	for (auto i : ans)
		cout << i << " ";
	cout << "\n";
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