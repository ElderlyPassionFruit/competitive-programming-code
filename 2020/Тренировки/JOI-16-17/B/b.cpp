#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

int n, m, k;
int b, c, a;
int t;
vector<int> have;

void read() {
	cin >> n >> m >> k;
	cin >> a >> b >> c;
	cin >> t;
	have.resize(m);
	for (auto &i : have)
		cin >> i;
}

vector<int> cnt;
vector<int> Time;

int get_len(int i) {
	return (i + 1 < m ? have[i + 1] : n + 1) - have[i];
}

void build() {
	k -= m;
	cnt.assign(m, 0);
	Time.assign(m, 0);
	for (int i = 0; i < m; i++) {
		Time[i] = b * (have[i] - 1);
		if (Time[i] > t) {
			cnt[i] = -1;
		} else {
			cnt[i] = min((t - Time[i]) / a + 1, get_len(i));
		}
	}
}

int ans;

void add() {
	int pos_add = -1;
	int cnt_add = -1;
	for (int i = 0; i < m; i++) {
		if (cnt[i] == -1) continue;
		if (cnt[i] == get_len(i)) continue;
		if (Time[i] + c * cnt[i] > t) continue;
		int can_add = min((t - Time[i] - c * cnt[i]) / a + 1, get_len(i) - cnt[i]);
		if (can_add > cnt_add) {
			cnt_add = can_add;
			pos_add = i;
		}
	}
	if (pos_add == -1) return;
	cnt[pos_add] += cnt_add;
}

void run() {
	build();

	while(k--) {
		add();
	}
	for (auto i : cnt) {
		if (i != -1) ans += i;
	}
}

void write() {
	cout << ans -1  << endl;
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