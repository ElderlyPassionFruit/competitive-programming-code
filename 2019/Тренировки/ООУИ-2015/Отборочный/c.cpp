#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector <int> help;
void read() {
	cin >> n;
	help.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		char x;
		cin >> x;
		if (x == '1')
			help[i] = 1;
	}
}

vector <int> pref;

int get(int l, int r) {
	return pref[r] - pref[l - 1];
}

void make() {
	pref.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1] + help[i];
	}
}
 
int ans;
void run() {
	make();
	ans = 0;
	for (int i = 1; i < n; i++) {
		bool flag = true;
		for (int j = i + 1; j <= n; j += i + 1) {
			int cnt = get(j - i, j - 1);
			if (cnt % 2 != help[j]) {
				flag = false;
				break;
			}
		}
		if (flag)
			ans++;
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