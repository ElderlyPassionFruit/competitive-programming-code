#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
string n;
int k;

void read() {
	cin >> n >> k;
}

ll calc(int len, int cnt) {
	if (cnt == 0) return 1;
	if (cnt == 1) return len * 9;
	if (cnt == 2) return len * (len - 1) / 2 * 9 * 9;
	return len * (len - 1) * (len - 2) / 6 * 9 * 9 * 9;
}

ll solve(string n, int cnt, int pos) {
	// Осталось слишком мало цифр
	if (cnt > n.size() - pos) return 0;
	
	// Дошли до конца
	if (pos == n.size()) {
		return cnt == 0;
	}
	
	// Всё остальное нули
	if (cnt == 0) return 1;
	
	ll ans = 0;
	
	// поставили n[pos]
	if (n[pos] > '0')
		ans += solve(n, cnt - 1, pos + 1);
	else
		ans += solve(n, cnt, pos + 1);
	//cout << "cnt = " << cnt << " pos = " << pos << " ans = " << ans << endl;
	
	int len = n.size() - pos - 1;
	int fcnt = 0;
	if (n[pos] - '0' > 1)
		fcnt = n[pos] - '0' - 1;
	//cout << "len = " << len << " fcnt = " << fcnt << endl;
	if (len >= cnt - 1)
		ans += calc(len, cnt - 1) * fcnt;
	//cout << "ans = " << ans << endl;
	if (len >= cnt && n[pos] > '0')
		ans += calc(len, cnt);
	//cout << "ans = " << ans << endl;
	return ans;
}

ll ans;

void run() {
	ans = solve(n, k, 0);
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