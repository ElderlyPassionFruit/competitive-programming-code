#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int x, y, z;

void read() {
	cin >> x >> y >> z;
}

const int MAXN = 101;

int len[MAXN];

bool check(int x) {
	return x >= 0 && x < MAXN;
}

vector<int> dx;

void run() {
	dx.push_back(1);
	dx.push_back(-1);
	dx.push_back(z);
	dx.push_back(-z);
	fill(len, len + MAXN, -1);
	queue<int> q;
	len[x] = 0;
	q.push(x);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto i : dx) {
			if (!check(x + i)) continue;
			if (len[x + i] != -1) continue;
			len[x + i] = len[x] + 1;
			q.push(x + i);
		}
	}
}

void write() {
	cout << len[y] << endl;
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