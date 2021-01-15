#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
long long a[MAXN], b[MAXN], now[MAXN], ans[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
}

struct event{
	int l, r;
	long long x, y;
	event() {
		l = r = x = y = 0;
	}
	event(int a, int b, long long c, long long d) {
		l = a, r = b, x = c, y = d;
	}
};

void relax(long long &val, int pos, event a) {
	if (pos > a.r || pos < a.l) return;
	val += a.x;
	val += (pos - a.l) * a.y;
}

int t;

void solve(int pos, vector <event> q) {
	long long val = now[pos];
	int m = q.size();
	for (int i = 0; i < m; i++) {
		relax(val, pos, q[i]);
		if (val >= b[pos]) {
			ans[pos] = t + i + 1;
			return;
		}
	}
}

void solve(vector<event> q) {
	for (int i = 0; i < n; i++) {
		now[i] = a[i];
	}

	vector<pair <int, pair <long long, long long> > > ev;
	for (auto i : q) {
		ev.push_back({i.l, {i.x, i.y}});
		ev.push_back({i.r + 1, {-i.x - (i.r - i.l + 1) * i.y, -i.y}});
	}

	sort(ev.begin(), ev.end());

	int pos = 0;
	long long x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		while (pos < ev.size() && ev[pos].first == i) {
			x += ev[pos].second.first;
			y += ev[pos].second.second;
			pos++;
		}
		a[i] += x;
		x += y;
	}

	for (int i = 0; i < n; i++) {
		if (a[i] >= b[i] && now[i] < b[i]) {
			solve(i, q);
		}
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		ans[i] = -1;
		if (a[i] >= b[i])
			ans[i] = 0;
	}

	int m;
	cin >> m;
	int sq = sqrt(m);
	vector<event> q;
	t = 0;
	for (int i = 0; i < m; i++) {
		if (!q.empty() && i % sq == 0) {
			solve(q);
			t += q.size();
			q.clear();
		}
		event a;
		cin >> a.l >> a.r >> a.x >> a.y;
		a.l--;
		a.r--;
		q.push_back(a);
	}

	if (!q.empty()) {
		solve(q);
		q.clear();
	}
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
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