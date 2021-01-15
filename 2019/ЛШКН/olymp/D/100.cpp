#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

const int MAXN = 1e5 + 10;
int a[MAXN], b[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
}

int ans[MAXN];
int now[MAXN];
int t;

struct event{
	int l, r, x, y;
};

struct Fadd{
	int pos, x, y;
};

bool cmp(Fadd a, Fadd b) {
	return tie(a.pos, a.x, a.y) < tie(b.pos, b.x, b.y);
}

void relax(int & val, int pos, event a) {
	if (pos > a.r || pos < a.l) return;
	val += a.x;
	val += (pos - a.l) * a.y;
}

void solve(int pos, vector<event> & q) {
	int val = now[pos];
	int m = q.size();
	for (int i = 0; i < m; i++) {
		relax(val, pos, q[i]);
		if (val >= b[pos]) {
			ans[pos] = i + t + 1;
			return;
		}
	}
}

void solve(vector<event> & q) {
	for (int i = 0; i < n; i++) {
		now[i] = a[i];
	}

	vector<Fadd> ev;
	for (auto i : q) {
		ev.push_back({i.l, i.x, i.y});
		ev.push_back({i.r + 1, -i.x - (i.r - i.l + 1) * i.y, -i.y});
	}

	sort(ev.begin(), ev.end(), cmp);

	int pos = 0;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		while (pos < ev.size() && ev[pos].pos == i) {
			x += ev[pos].x;
			y += ev[pos].y;
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
		if (a[i] >= b[i])
			ans[i] = 0;
		else
			ans[i] = -1;
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
		event x;
		cin >> x.l >> x.r >> x.x >> x.y;
		x.l--;
		x.r--;
		q.push_back(x);
	}
	if (!q.empty()) {
		solve(q);
		q.clear();
	}
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << "\n";
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