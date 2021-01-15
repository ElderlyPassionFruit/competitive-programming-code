#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	string name;
	int x, y;
};

int x, y;
vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, 1, -1};
int dir;

int n;
vector<event> a;

void read() {
	cin >> x >> y;
	string s;
	cin >> s;
	if (s == "LEFT") {
		dir = 0;
	}
	if (s == "RIGHT") {
		dir = 1;
	}
	if (s == "UP") {
		dir = 2;
	}
	if (s == "DOWN") {
		dir = 3;
	}
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.name >> i.x >> i.y;
}

int get(int x) {
	return (abs(x) + 1) / 2;
}

bool check(int x1, int y1, int t) {
	return get(x + dx[dir] * t - x1) + get(y + dy[dir] * t - y1) <= t;
}

const int INF = 1e15;
pair <int, int> ans;

void run() {
	ans = make_pair(INF, INF);
	for (int i = 0; i < n; i++) {
		int l = 0, r = INF;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (check(a[i].x, a[i].y, mid))
				r = mid;
			else
				l = mid;
		}
		//cout << r << " " << i << endl; 
		chkmin(ans, make_pair(r, i));
	}
}

void write() {
	cout << a[ans.second].name << endl;
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