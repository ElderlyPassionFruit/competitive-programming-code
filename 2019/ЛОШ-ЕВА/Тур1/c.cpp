#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, k;
vector<pair <int, char> > help;
void read() {
	cin >> n;
	int w, b, c;
	cin >> w >> b >> c;
	help.push_back({w, 'W'});
	help.push_back({b, 'B'});
	help.push_back({c, 'C'});
	sort(help.begin(), help.end());
	reverse(help.begin(), help.end());
	cin >> k;
}

vector<char> ans;
void run() {
	int w = 0, b = 0, c = 0;
	for (int i = 0; i < n; i++) {
		if (w == k) {
			w -= k;
			help[0].first += k;
		}
		if (b == k) {
			b -= k;
			help[1].first += k;
		}
		if (c == k) {
			c -= k;
			help[2].first += k;
		}

		bool flag = false;
		for (int k = 0; k < 3; k++) {
			auto j = help[k];
			if (j.first == 0)
				continue;
			if (i > 0 && ans[i - 1] == j.second)
				continue;
			if (i > 6 && ans[i - 7] == j.second)
				continue;
			help[k].first--;
			ans.push_back(help[k].second);
			if (k == 0) w++;
			if (k == 1) b++;
			if (k == 2) c++;
			flag = true;
			break;
		}	

		if (flag)
			continue;

		cout << "NO\n";
		exit(0);
	}
}

void write() {
	cout << "YES\n";
	for (auto i : ans)
		cout << i;
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