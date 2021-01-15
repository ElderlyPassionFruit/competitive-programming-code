#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
int arr[MAXN];
int n, m;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

void run() {
	cin >> m;
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		set <int> ans;
		for (int j = l; j <= r; j++) {
			ans.insert(arr[j]);
		}
		cout << ans.size() << endl;
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