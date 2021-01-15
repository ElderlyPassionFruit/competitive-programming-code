#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, q;
vector <int> a;
void read() {
	cin >> n >> q;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
}

void run() {
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int pos;
			cin >> pos;
			pos--;
			cout << a[pos] << " ";
		}
		if (type == 2) {
			int x;
			cin >> x;
			for (int j = 0; j < n; j++) {
				if (a[j] > x)
					a[j] -= x;
			}
			sort(a.begin(), a.end());
		}
	}
}

void write() {

}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}