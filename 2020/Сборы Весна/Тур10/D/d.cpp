#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int n;
vector<pair<int, int>> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second;
}

int ans;

void relax(vector<pair<int, int>> & a) {
	priority_queue<int> q;
	ll sum = 0;
	for (auto i : a) {
		q.push(i.first);
		sum += i.first;
		while (sum > i.second + i.first) {
			int x = q.top();
			q.pop();
			sum -= x;
		}
		chkmax(ans, (int)q.size());
		if (ans == n) return;
	}
}

void run() {
	ans = 0;
	sort(all(a), [&] (pair<int, int> i, pair<int, int> j) {
		if (i.first + i.second != j.first + j.second) return i.first + i.second > j.first + j.second;
		return tie(i.first, i.second) < tie(j.first, j.second);
	});
	relax(a);
	reverse(all(a));
	relax(a);
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