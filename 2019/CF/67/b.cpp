#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n;
string s;
vector<vector<int>> help;
void read() {
	cin >> n >> s;
	vector<int> num(26);
	for (int i = 0; i < n; i++) {
		num[s[i] - 'a']++;
		help.push_back(num);
	}

}
vector<int> ans;
void run() {
	int q;
	cin >> q;
	while (q--) {
		cin >> s;
		vector<int> num(26);
		for (auto i : s) {
			num[i - 'a']++;
		}

		int l = -1, r = n - 1; 
		while (l < r - 1) {
			int mid = (l + r) / 2;
			bool flag = false;
			for (int i = 0; i < 26; i++) {
				flag |= help[mid][i] < num[i];
			}
			if (flag)
				l = mid;
			else
				r = mid;
		}		
		ans.push_back(r + 1);
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