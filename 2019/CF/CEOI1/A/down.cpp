#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;

struct event{
	int x, y, ind;
};

int n, t;
vector<event> a;
void read() {
	cin >> n >> t;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		a[i].ind = i + 1;
	}
}

bool operator<(event a, event b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

void no() {
	cout << "NO\n";
	exit(0);
}

struct vert{
	int up, down, x;
};

vector<int> g[MAXN];

const int INF = 1e9 + 10;

vector<int> ans;

void solve(vector<event> & help, int l, int r) {
	int n = help.size();
	for (int i = 0; i < n; i++) {
		if (help[i].y >= l - 1 && help[i].y <= r + 1) {
			ans.push_back(help[i].ind);
			for (int j = i - 1; j >= 0; j--)
				ans.push_back(help[j].ind);
			for (int j = i + 1; j < n; j++)
				ans.push_back(help[j].ind);
			return;
		}
	}
	assert(false);
}

bool check(int l, int r, int x) {
	return l - 1 <= x && r + 1 >= x;
}

bool cross(int l, int r, pair <int, int> ud) {
	return	check(l, r, ud.first) || check(l, r, ud.second) || check(ud.first, ud.second, l) || check(ud.first, ud.second, r);
}

void solve(vector<event> & help, vector<pair <int, int> > & up_down) {
	int n = help.size();
	int m = up_down.size();
	int pos_up_down = 0;

	for (int i = 0; i < n; i++) {
		int pos = i + 1;
		vector<event> need;
		need.push_back(help[i]);
		while (pos < n && help[pos].y == help[pos].y) {
			need.push_back(help[pos]);
			pos++;
		}
		pos--;

		int l = need[0].y, r = need.back().y;
		while (pos_up_down < m && !cross(l, r, up_down[pos_up_down]))
			pos_up_down++;
		if (pos_up_down == m)
			no();
		
		solve(need, up_down[pos_up_down].first, up_down[pos_up_down].second);
		i = pos;
	}	

	//make new up_down
	up_down.clear();
	int l = -INF, r = -INF;
	for (auto i : help) {
		if (i.y > r + 1) {
			if (l != INF) {
				up_down.push_back({l, r});
			}

			l = i.y, r = i.y;
		}
		else {
			r = i.y;
		}
	}

	if (l != INF) {
		up_down.push_back({l, r});
	}
}

void run() {
	sort(a.begin(), a.end());
	for (int i = 1; i < n; i++) {
		if (a[i].x - a[i - 1].x > 1)
			no();
	}

	vector<pair <int, int> > up_down;
	up_down.push_back({-INF, INF});

	for (int i = 0; i < n; i++) {
		int pos = i + 1;
		vector<event> help;
		help.push_back(a[i]);
		while (pos < n && a[pos].x == a[i].x){
			help.push_back(a[pos]);
			pos++;
		}
		pos--;
		solve(help, up_down);
		i = pos;
	}
}

void write() {
	cout << "YES\n";
	for (auto i : ans)
		cout << i << "\n"; 
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