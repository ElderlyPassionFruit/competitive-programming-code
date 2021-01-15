#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

map<int, vector<string>> ans[3];
vector<string> have = {"If you want to call a taxi, you should call:", "If you want to order a pizza, you should call:", "If you want to go to a cafe with a wonderful girl, you should call:"};
int n;

bool checkSorted(string s) {
	return s[0] > s[1] && s[1] > s[3] && s[3] > s[4] && s[4] > s[6] && s[6] > s[7];
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		string s;
		cin >> s;
		int cnt0 = 0, cnt1 = 0, cnt2 = 0;
		while (x--) {
			string have;
			cin >> have;
			set<char> now;
			now.insert(have[0]);
			now.insert(have[1]);
			now.insert(have[3]);
			now.insert(have[4]);
			now.insert(have[6]);
			now.insert(have[7]);
			if (now.size() == 1) {
				cnt0++;
			} else if (now.size() == 6 && checkSorted(have)) {
				cnt1++;
			} else {
				cnt2++;
			}
		}
		//cout << "i = " << i << " cnt0 = " << cnt0 << " cnt1 = " << cnt1 << " cnt2 = " << cnt2 << endl;
		ans[0][cnt0].push_back(s);
		ans[1][cnt1].push_back(s);
		ans[2][cnt2].push_back(s);
	}
	for (int i = 0; i < 3; i++) {
		int mx = 0;
		for (auto j : ans[i]) {
			mx = max(mx, j.first);
		}
		cout << have[i];
		for (int j = 0; j < (int)ans[i][mx].size(); j++) {
			if (j == 0) {
				cout << " ";
			} else {
				cout << ", ";
			}
			cout << ans[i][mx][j];
		}
		cout << ".";
		cout << endl;
	}
	return 0;
}