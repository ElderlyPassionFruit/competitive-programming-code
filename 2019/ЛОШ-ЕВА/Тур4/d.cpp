#include <bits/stdc++.h>

using namespace std;
#define int long long

vector<vector<int> > help;
int n;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, f, a, b;
		cin >> s >> f >> a >> b;
		help.push_back({s, f, a, b});
	}
}

int get(int pos, int max_x) {
	int s, f, a, b;
	s = help[pos][0];
	f = help[pos][1];
	a = help[pos][2];
	b = help[pos][3];
	if (s > max_x) return 0;
	f = min(f, max_x);

	int cnt_full = (f - s + 1) / (a + b);
	s += cnt_full * (a + b);

	return cnt_full * a + min(f - s + 1, a);
}

bool check(int max_x) {
	int fans = 0;
	for (int i = 0; i < n; i++) {
		fans += get(i, max_x);
		fans %= 2;
	}
	return fans;
}

int ans;
void run() {
	if (!check(1e9 + 10)) {
		ans = 0;
		return;
	}
	int l = -1, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
}

void write() {
	cout << ans << endl;
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();	
	run();
	write();
	return 0;
}