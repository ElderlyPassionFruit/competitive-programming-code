#include <bits/stdc++.h>

using namespace std;
#define int long long

bool check(int a, int b) {
	cout << 1 << " " << a << " " << b << endl;
	string ans;
	cin >> ans;
	return ans == "YES";
}

void wr(vector <int> ans) {
	cout << 0 << " ";
	for (int i = 0; i < ans.size() - 1; i++)
		cout << ans[i] << " ";
	cout << ans[ans.size() - 1] << endl;
	cout.flush();
}

bool cmp(const int & a, const int & b) {
	return check(a, b);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> fans(n);
	for (int i = 0; i < n; i++) {
		fans[i] = i + 1;
	}
	stable_sort(fans.begin(), fans.end(), cmp);
	wr(fans);
	return 0;
}	