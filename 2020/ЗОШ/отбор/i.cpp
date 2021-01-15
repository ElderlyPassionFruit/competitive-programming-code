#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};
#define int ll

struct event{
	string fans;
	int time;
	event() {}
	event(string a, int t) {
		fans = a, time = t;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.time, a.fans) < tie(b.time, b.fans);
} 

int get_time(string s) {
	int ans = 0;
	int t1 = 0;
	reverse(all(s));
	while (s.back() != ':') {
		t1 *= 10;
		t1 += s.back() - '0';
		s.pop_back();
	}
	s.pop_back();
	ans += t1 * 60 * 60;
	t1 = 0;
	while (s.back() != ':') {
		t1 *= 10;
		t1 += s.back() - '0';
		s.pop_back();
	}
	s.pop_back();
	ans += t1 * 60;
	t1 = 0;
	while (!s.empty()) {
		t1 *= 10;
		t1 += s.back() - '0';
		s.pop_back();
	}
	ans += t1;
	return ans;
}

int n;
vector<event> a;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int t = get_time(s);
		a.push_back({s, t});
		a.push_back({s, t + 60 * 60 * 12});
	}
	sort(all(a));
}

pair<int, string> ans;

void run() {
	int now = 0;
	for (int i = 0; i < n; i++)
		now += a[n - 1].time - a[i].time;
	ans = {now, a[n - 1].fans};
	for (int i = n; i < 2 * n; i++) {
		now -= a[i - 1].time - a[i - n].time;
		now += (a[i].time - a[i - 1].time) * (n - 1);
		chkmin(ans, make_pair(now, a[i].fans));
	}
}

void write() {
	cout << ans.second << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}










