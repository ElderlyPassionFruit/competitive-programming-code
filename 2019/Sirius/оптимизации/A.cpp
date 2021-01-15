#include <bits/stdc++.h>

using namespace std;

//#define int long long

struct line{
	int k, b;
	line () {
		k = 0, b = -1e9;
	}
	line (int x, int y) {
		k = x, b = y;
	}
};

double cross(line a, line b) {
	return (double) (b.b - a.b) / (a.k - b.k);
}

struct cht {
	deque <line> l;
	deque <double> p;

	cht () {
		l = {}, p = {};
	}

	void add(line a) {
		while (!p.empty() && cross(l[0], a) >= p[0]) 
			p.pop_front(), l.pop_front();
		l.push_front(a);
		if (l.size() >= 2)
			p.push_front(cross(l[0], l[1]));
	}

	int get(int x) {
		int i = lower_bound(p.begin(), p.end(), x) - p.begin();
		return l[i].k * x + l[i].b;
	}
};

const int MAXN = 2*1e4 + 10;
pair <int, int> trees[MAXN];

int n;
int full_cost = 0;
int w[MAXN], len[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> trees[i].first >> trees[i].second;
	}
	for (int i = n - 1; i >= 0; i--) {
		len[i] = len[i + 1] + trees[i].second;
	}

	w[0] = trees[0].first;
	for (int i = 0; i < n; i++) {
		w[i] = w[i - 1] + trees[i].first;
	}

	for (int i = 0; i < n; i++) {
		full_cost += trees[i].first * len[i];
	}
}

cht help;
int fans = 0;
void run() {
	help.add(line(-w[0], w[0] * len[0]));
//	cout << "i = 0\n w[i] = " << w[0] << " len[i] = " << len[0] << endl;
	for (int i = 1; i < n; i++) {
		fans = max(fans, len[i] * w[i] + help.get(len[i]));
/*		cout << "i = " << i << endl;
		cout << "w[i] = " << w[i] << " len[i] = " << len[i] << " opt_point = " << help.get(len[i]) << endl;
		cout << "fans = " << fans << endl;
		cout << endl;
*/		help.add(line(-w[i], w[i] * len[i]));
	}
/*	cout << "dp:\n";
	for (int i = 0; i < n; i++) {
		cout << dp[i] << " ";
	}
	cout << endl; */
}

void write() {
/*	cout << "len:\n";
	for (int i = 0; i < n; i++) {
		cout << len[i] << " ";
	}
	cout << endl;
	cout << "w\n";
	for (int i = 0; i < n; i++) {
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "full_cost = " << full_cost << endl;
*/	cout << full_cost - fans << endl;
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