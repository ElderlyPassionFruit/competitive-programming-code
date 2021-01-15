#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;
vector <pair <int, int> > a;
set <pair <int, int> > help;

pair <int, int> ed(int a, int b) {
	if (a > b)
		swap(a, b);
	return {a, b};
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a.push_back({x, y});
		help.insert({x, y});
	}
}

int ans = 0;
#define x first
#define y second
pair <int, int> operator-(pair <int, int> a, pair <int, int> b) {
	return {a.x - b.x, a.y - b.y};
}

pair <int, int> operator+(pair <int, int> a, pair <int, int> b) {
	return {a.x + b.x, a.y + b.y};
}

int check(pair <int, int> a, pair <int, int> b) {
	int ans = 0;

	auto v = a - b;
	pair <int, int> x1 = {v.second, -v.first};

	auto check1 = a + x1;
	auto check2 = b + x1;
	if (help.count(check1) && help.count(check2))
		ans++;

	check1 = a - x1;
	check2 = b - x1;

	if (help.count(check1) && help.count(check2))
		ans++;

	return ans;
}

void run() {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
	//		cout << "i = " << i << " j = " << j << " check(a[i], a[j]) = " << check(a[i], a[j]) << endl;
			ans += check(a[i], a[j]);
		}
	}
	ans /= 4;
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