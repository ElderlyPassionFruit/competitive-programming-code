#include <bits/stdc++.h>

using namespace std;
//#define int long long
int n;
void read() {
	cin >> n;
}
const int MAXN = 3010;

int k;
int ans[MAXN];
void run() {
	cout << "? " << 1 << " " << n << endl;
	
	cin >> k;
	int now = 2;
	int last_ans = 1;
	ans[0] = 1;

	for (int i = 2; i <= n; i++) {
		cout << "? " << 1 << " " << i << endl;
		int fans;
		cin >> fans;
		if (fans == last_ans + 1) {
			ans[i - 1] = now++;
		}
		else {
			int l = 1, r = i;
			while (l < r - 1) {
				int mid = (l + r) / 2;
				cout << "? " << mid << " " << i << endl;
				int help;
				cin >> help;
				vector <int> h;
				for (int j = mid - 1; j < i - 1; j++)
					h.push_back(ans[j]);

				sort(h.begin(), h.end());
				int h_sz = 1;
				for (int j = 1; j < h.size(); j++)
					if (h[j] != h[j - 1])
						h_sz++;
				if (help == h_sz) {
					l = mid;
				}
				else {
					r = mid;
				}
			}
			ans[i - 1] = ans[l - 1];
		}
		last_ans = fans;
	}	

}

void write() {
	cout << "Ready!" << endl;
	cout << k << endl;
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;
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