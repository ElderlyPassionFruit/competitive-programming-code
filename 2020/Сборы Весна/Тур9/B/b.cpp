#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
void no() {
	cout << -1 << endl;
	exit(0);
} 
int sum_all;
int n;
vector<int> a;
int sum_b, x;

void read() {
	sum_all = 0; sum_b = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		sum_all += x;
	}
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	sort(all(a));
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		sum_b += x;
	}
	cin >> x;
}

void check() {
	int sum = sum_b;
	for (auto i : a)
		sum += i;
	if (sum < sum_all)
		no();
}

const int MAXA = 1e5 + 10;
int cnt[MAXA];

void build() {
	/*for (auto i : a) {
		cnt[1]++;
		cnt[i + 1]--;
	}
	for (int i = 2; i < MAXA; i++) {
		cnt[i] += cnt[i - 1];
	}*/
	for (auto i : a) {
		for (int l = 1; l <= i; l++) {
			cnt[l]++;
		}
	}
}	

int ans;

void run() {
	if (sum_all == 0) {
		no();
	}
	sum_all = sum_all / 2 + 1;
	check();
	//cout << sum_all << endl;
	build();
	ans = 0;
	/*cout << "cnt = " << endl;
	for (int i = 1; i <= 11; i++) {
		cout << cnt[i] << " ";
	}
	cout << endl;*/
	for (int i = 1; i < MAXA && sum_all > 0; i++) {
		int cost = i * i - (i - 1) * (i - 1);
		if (cost <= x) {
			int add = min(sum_all, cnt[i]);
			ans += add * cost;
			sum_all -= add;
		} else {
			int add;
			add = min(sum_all, sum_b);
			ans += add * x;
			sum_b -= add;
			sum_all -= add;
			add = min(sum_all, cnt[i]);
			ans += add * cost;
			sum_all -= add;
		}
	}
	int add = min(sum_all, sum_b);
	sum_all -= add;
	ans += add * x;
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