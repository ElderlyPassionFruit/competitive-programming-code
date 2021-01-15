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
	if (n > 10)
		exit(0);
	for (int i = 0; i < n; i++) {
		int x, y, ind;
		cin >> x >> y;
		ind = i + 1;
		a.push_back({x, y, ind});
	}
}

bool operator<(event a, event b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

void no() {
	cout << "NO\n";
	exit(0);
}

vector<int> dx = {0, 1, 0, -1}, dy = {-1, 0, 1, 0};
vector<int> ans;

map <pair <int, int>, int > used;

int fans = 0;

void get_cnt(int x, int y, int c) {
	used[{x, y}] = c;
	fans++;
	if (fans > 100)
		return;
	for (int i = 0; i < 4; i++) {
		if (used[{x + dx[i], y + dy[i]}] != c)
			get_cnt(x + dx[i], y + dy[i], c);
	}
}

bool check(event a, event b) {
	return abs(a.x - b.x) <= 1 && abs(a.y - b.y) <= 1;
}

bool check(vector<event> a) {
	used.clear();
	used[{a[0].x, a[0].y}] = 1;
	int n = a.size();
	int c = 100;
	for (int i = 1; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < i; j++)
			flag |= check(a[i], a[j]);
		if (!flag)
			return false; 
		fans = 0;
		get_cnt(a[i].x, a[i].y, c++);
		used[{a[i].x, a[i].y}] = 1;
		if (fans < 100)
			return false;
	}
	for (auto i : a) {
		ans.push_back(i.ind);
	}
	return true;
}


void run() {
	sort(a.begin(), a.end());

	do {
		if(check(a))
			return;
	} while (next_permutation(a.begin(), a.end()));
	no();
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