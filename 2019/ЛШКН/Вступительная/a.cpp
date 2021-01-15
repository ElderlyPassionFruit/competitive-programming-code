#include <bits/stdc++.h>

using namespace std;
#define int long long
int k;
int n;
vector <int> help;
void read() {
	string s;
	cin >> k >> s;
	n = s.size();
	k = min(k, n);
	help.resize(n);
	for (int i = 0; i < n; i++)
		help[i] = s[i] - 'a';
}

int ans;
void run() {
	/*cout << "help = " << endl;
	for (auto i : help)
		cout << i << " ";
	cout << endl;
	cout << "n = " << n << endl;*/
	ans = 0;
	for (int type = 0; type < 26; type++) {
		int l = 0, r = -1;
		int have = k;
		while (l < n && r < n) {
			while (r < n - 1 && (have || help[r + 1] == type)) {
				r++;
				if (help[r] != type)
					have--;
			}
			ans = max(ans, r - l + 1);
			l++;
			if (help[l - 1] == type)
				have++;
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