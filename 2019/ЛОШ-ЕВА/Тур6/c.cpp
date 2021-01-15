#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int gen(int a1, int a2) {
	int ans = abs(a[0] - a1) + abs(a[1] - a2);
	for (int i = 2; i < n; i++) {
		int a3 = a2 - a1;
		a1 = a2;
		a2 = a3;
		ans += abs(a[i] - a2);
	}
	return ans;
}

pair <int, pair <int, int> >  ans = {1e18, {-1, -1}};


void run() {
	for (int i = -100; i <= 100; i++) {
		for (int j = -100; j <= 100; j++) {

			ans = min(ans, {gen(i, j), {-i, -j}});
		}
	}
}

void write() {
	cout << ans.first << endl;
	cerr << -ans.second.first << " " << -ans.second.second << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w",stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}