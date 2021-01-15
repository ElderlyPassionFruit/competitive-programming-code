#include <bits/stdc++.h>

using namespace std;
#define int long long
int h, n, m, a, b;
void read() {
	cin >> h >> n >> m >> a >> b;
}
vector <char> ans;
void run() {
	int x = (n + m) / (m + 1);
	int y = (m + n) / (n + 1);
	if (x > a) {
		cout << "NO" << endl;
		exit(0);
	}
	if (y > b) {
		cout << "NO" << endl;
		exit(0);
	}
	cout << "YES" << endl;
	if (h == 0)
		exit(0);
	bool flag = false;
	if (n < m) {
		swap(n, m);
		swap(a, b);
		flag = true;
	}

	vector <int> groups;
	int cnt = n / (m + 1);
	for (int i = 0; i < m + 1; i++) {
		groups.push_back(cnt);
	}

	for (int i = 0; i < n % (m + 1); i++) {
		groups[i]++;
	}

	for (auto i : groups) {
		for (int j = 0;  j < i; j++) {
			ans.push_back('G');
		}
		ans.push_back('B');
	}
	ans.pop_back();
	map <char, char> help;
	help['G'] = 'B';
	help['B'] = 'G';
	if (flag) {
		for (int i = 0; i < ans.size(); i++) {
			ans[i] = help[ans[i]];
		}
	}
}

void write() {
	if (h) {
		for (auto i : ans)
			cout << i;
		cout << endl;
	}
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