#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int type, x, ind;
	event() {}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type, a.ind) < tie(b.x, b.type, b.ind);
}

struct segment{
	int l, r;
};

int n, m;
vector<event> a;
vector<segment> have;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		event x;
		cin >> x.x;
		x.type = 2;
		x.ind = i;
		a.push_back(x);
	}
	for (int i = 0; i < m; i++) {
		event x;
		cin >> x.x;
		int l = x.x;
		x.type = 1;
		x.ind = i;
		a.push_back(x);
		cin >> x.x;
		int r = x.x;
		x.type = 3;
		a.push_back(x);
		have.push_back({l, r});
	}
}

struct fset{
	int r, ind;
};

bool operator<(const fset & a, const fset & b) {
	return tie(a.r, a.ind) > tie(b.r, b.ind);
}

vector<vector<int> > can;

vector<int> ans;

void build() {
	can.resize(n);
	multiset<fset> q;
	for (auto e : a) {
		if (e.type == 1) {
			q.insert({have[e.ind].r, e.ind});
		}
		else if (e.type == 3) {
			q.erase({e.x, e.ind});
		}
		else {
			if (q.empty()) {
				cout << "No" << endl;
				exit(0);
			}
			auto it = q.begin();
			int x = 0;
			while (x < 3 && it != q.end()) {
				can[e.ind].push_back(it->ind);
				x++;
				++it;
			}
		}
	}
}

const int MAXN = 1e5 + 10;
bool dp[MAXN][3];
int par[MAXN][3];

void calc() {
	for (int i = 0; i < can[0].size(); i++)
		dp[0][i] = true;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < can[i].size(); j++) {
			dp[i][j] = false;
			for (int k = 0; k < can[i - 1].size(); k++) {
				if (dp[i - 1][k] && can[i][j] != can[i - 1][k]) {
					dp[i][j] = true;
					par[i][j] = k;
					break;
				}
			}
		}
	}
}

void make_ans() {
	int pos = -1;
	ans.resize(n);
	for (int i = 0; i < can[n - 1].size(); i++) {
		if (dp[n - 1][i]) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "No" << endl;
		exit(0);
	}
	for (int i = n - 1; i >= 0; i--) {
		ans[i] = can[i][pos];
		pos = par[i][pos];
	}
}

void run() {
	sort(all(a));
	build();
	calc();
	make_ans();
}

void write() {
	cout << "Yes" << endl;
	for (auto i : ans)
		cout << i + 1 << " ";
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