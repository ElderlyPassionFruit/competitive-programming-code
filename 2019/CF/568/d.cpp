#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n;
vector<pair<int, int> > a;
void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());
}

int cnt = 0;
map <int, int> help;

void add(int x) {
	if (help[x] == 0)
		cnt++;
	help[x]++;
}

void del(int x) {
	if (help[x] == 1)
		cnt--;
	help[x]--;
}

bool check() {
	return cnt == 1;
}

int ans = -1;
void run() {
	for (int i = 1; i < n; i++)
		add(a[i].first - a[i - 1].first);

	if (check()) {
		ans = a[0].second + 1;
		return;
	}

	del(a[1].first - a[0].first);
	if (check()) {
		ans = a[0].second + 1;
		return;
	}
	add(a[1].first - a[0].first);

	del(a[n - 1].first - a[n - 2].first);
	if (check()) {
		ans = a[n - 1].second + 1;
		return;
	}
	add(a[n - 1].first - a[n - 2].first);

	for (int i = 1; i <= n - 2; i++) {
		del(a[i].first - a[i - 1].first);
		del(a[i + 1].first - a[i].first);
		add(a[i + 1].first - a[i - 1].first);

		if (check()) {
			ans = a[i].second + 1;
			return;
		}

		add(a[i].first - a[i - 1].first);
		add(a[i + 1].first - a[i].first);
		del(a[i + 1].first - a[i - 1].first);
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