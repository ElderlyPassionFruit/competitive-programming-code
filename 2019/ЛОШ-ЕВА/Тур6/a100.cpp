#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
int n;
vector<int> a, h1, h2;
int k;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int type, val;
		cin >> type >> val;
		if (type == 1) h1.push_back(val);
		if (type == 2) h2.push_back(val);
	}
}

double ans;

double get(int x, int t1, int t2) {
	double ans1 = (double) x * (100 + t1) / 100;
	double ans2 = x + t2;
	return max(ans1, ans2);
}

void run() {
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	sort(h1.begin(), h1.end());
	reverse(h1.begin(), h1.end());
	sort(h2.begin(), h2.end());
	reverse(h2.begin(), h2.end());

	while (h1.size() < n)
		h1.push_back(0);
	while (h1.size() > n)
		h1.pop_back();

	while (h2.size() < n)
		h2.push_back(0);
	while (h2.size() > n)
		h2.pop_back();

	reverse(h2.begin(), h2.end());

	for (int i = 0; i < n; i++) {
		ans += get(a[i], h1[i], h2[i]);
	}
}

void write() {
	cout.precision(20);
	cout << ans << endl;
}

signed main() {
	freopen("costumes.in", "r", stdin);
	freopen("costumes.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}