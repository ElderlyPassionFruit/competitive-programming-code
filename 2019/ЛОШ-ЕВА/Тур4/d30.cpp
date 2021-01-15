#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
const int MAXF = 1010;
vector<pair <int, int> > seg;

void gen(int s, int f, int a, int b) {
	int num = s;
	while (num <= f) {
		seg.push_back({num, min(num + a, f + 1)});
		num += a + b;
	}
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, a, b, f;
		cin >> s >> f >> a >> b;
		gen(s, f, a, b);
	}
}

int ans = 0;

void run() {
	map <int, pair <int, int> > help;
	for (auto i : seg) {
		help[i.first].first++;
		if (!help.count(i.first + 1))
			help[i.first + 1] = {0, 0};
		if (!help.count(i.first - 1))
			help[i.first - 1] = {0, 0};
		help[i.second].second++;
		if (!help.count(i.second + 1))
			help[i.second + 1] = {0, 0};
		if (!help.count(i.second - 1))
			help[i.second - 1] = {0, 0};
	}

	int cnt = 0;
	for (auto i : help) {
		cnt += i.second.first;
		cnt -= i.second.second;
		if (cnt % 2 == 1) {
			ans = i.first;
			return;
		}
	}
}

void write() {
	cout << ans << endl;
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