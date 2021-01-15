#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, v;
vector<pair <int, int> > a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.second >> i.first;
	cin >> v;
}

int ans1, ans2;

bool check(pair <int, int> a, pair <int, int> b) {
	int have = a.first - b.first;
	int need = (abs(a.second - b.second) + v - 1) / v;
	return have >= need;
}

int get1(vector<pair <int, int> > a) {
	pair <int, int> now = {0, 0};
	int ans = 0;
	for (auto i : a) {
		if (!check(i, now))
			break;
		ans++;
		now = i;
	} 
	return ans;
}

int get2(vector<pair <int, int> > a) {
	pair <int, int> now = a[0];
	int ans = 1;
	for (auto i : a) {
		if (now == i) continue;
		if (!check(i, now))
			break;
		ans++;
		now = i;	
	}
	return ans;
}

void run() {
	sort(a.begin(), a.end());
	ans1 = 0;
	do {
		ans1 = max(ans1, get1(a));
	} while (next_permutation(a.begin(), a.end()));

	sort(a.begin(), a.end());
	ans2 = 0;
	do {
		ans2 = max(ans2, get2(a));
	} while (next_permutation(a.begin(), a.end()));
}

void write() {
	cout << ans1 << " " << ans2 << endl;
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