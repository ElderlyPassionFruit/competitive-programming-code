#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;

vector <int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
}
int ans = 0;
const int MAXN = 1e5 + 10;
void run() {
	map <int, int> help;
	map <int, int> fans;
	for (int i = 0; i < n; i++) {
		if (help[a[i]] > 0)
		fans[help[a[i]]]--;

		if (fans[help[a[i]]] == 0)
			fans.erase(help[a[i]]);
		help[a[i]]++;
		
		fans[help[a[i]]]++;
	/*	cout << "help = " << endl;
		for (auto j : help) {
			cout << j.first << " " << j.second << endl;
		}

		cout << "fans = " << endl;
		for (auto j : fans) {
			cout << j.first << " " << j.second << endl;
		}
		cout << endl;*/
		if ((int) fans.size() == 1) {
			int num = 0;
			int sz = 0;
			for (auto j : fans) {
				num = j.first;
				sz = j.second;
			}
			if (sz == 1 || num == 1) {
				ans = i + 1;
			}
		}
		if ((int) fans.size() == 2) {
			int num = -1;
			int num2 = -1;
			int sz = 0;
			int sz2 = -1;
			int cnt = 0;
			for (auto j : fans) {
				if (cnt == 0) {
					num = j.first;
					sz = j.second;
				}
				else {
					num2 = j.first;
					sz2 = j.second;
				}
				cnt++;
			}

			if (num == num2 - 1 && sz2 == 1) {
				ans = i + 1;
			}

			if (num == 1 && sz == 1) {
				ans = i + 1;
			}
		}
	}
}

void write() {
	cout << ans << endl;
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