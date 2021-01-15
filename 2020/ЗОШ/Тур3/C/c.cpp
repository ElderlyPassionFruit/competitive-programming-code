#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
ll n;

void read() {
	cin >> n;
}

struct prime{
	int x, cnt;
	prime() {}
	prime(int a, int b) {
		x = a, cnt = b;
	}
};

vector<prime> a;
const int MAXC = 100;
vector<int> have[MAXC];

void get(int n, int sum, int pos) {
	//cout << n << " " << sum << " " << pos << endl;
	have[sum].push_back(n);
	if (pos + 1 < a.size()) get(n, sum, pos + 1);
	for (; pos < (int)a.size(); pos++) {
		int x = 1;
		for (int i = 0; i < a[pos].cnt; i++) {
			x *= a[pos].x;
			get(n * x, sum + i + 1, pos + 1);
		}
	}
}

vector<int> ans;

void run() {
	for (int i = 2; i * i <= n && i <= 100; i++) {
		if (n % i == 0) {
			a.push_back({i, 0});
			while (n % i == 0) {
				n /= i;
				a[a.size() - 1].cnt++;
			}
		}
	}
	if (n != 1) {
		a.push_back({n, 1});
	}
	//cout << "a = " << endl;
	//for (auto i : a)
	//	cout << i.x << " " << i.cnt << endl;
	get(1, 0, 0);
	ans = {};
	for (int i = 0; i < MAXC; i++) {
		sort(all(have[i]));
		have[i].resize(unique(all(have[i])) - have[i].begin());
		if (have[i].size() > ans.size())
			ans = have[i];
	}
}

void write() {
	cout << ans.size() << endl;
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