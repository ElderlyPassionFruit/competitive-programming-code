#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m;
vector <int> a, b;
void read() {
	cin >> n;
	a.assign(n, 0);
	for (auto &i : a)
		cin >> i;
	cin >> m;
	b.assign(m, 0);
	for (auto &i : b)
		cin >> i;
}

vector <int> z_finction(vector <int> s) {
	int sz = s.size();
	vector <int> z(sz, 0);
	int l = 0, r = 0;
	for (int i = 1; i < sz; i++) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (z[i] + i < sz && s[z[i]] == s[z[i] + i])
			z[i]++;
		if (r < z[i] + i - 1)
			l = i, r = z[i] + i - 1;
	}
	return z;
}

int make(int a, int b) {
	int g = __gcd(a, b);
	a /= g;
	b /= g;
	return a * 1000 + b;
}

vector <int> ans;
void run() {
	if (n == 1) {
		for (int i = 1; i <= m; i++)
			ans.push_back(i);
		return;
	}
	vector <int> help;
	for (int i = 0; i < n - 1; i++)
		help.push_back(make(a[i], a[i + 1]));
	help.push_back(-1);
	for (int i = 0; i < m - 1; i++)
		help.push_back(make(b[i], b[i + 1]));

	auto z = z_finction(help);
	for (size_t i = 0; i < z.size(); i++) {
		if (z[i] == n - 1)
			ans.push_back(i - n + 1);
	}
}

void write() {
	cout << (int) ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
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