#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;
const int MAXN = 2e6;
int n, k;
int dist[MAXN];

vector<int> a;

int readInt() {
	int ans = 0;
	string s;
	cin >> s;
	for (auto i : s)
		ans *= 2, ans += i - '0';
	return ans;
}

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x;
		x = readInt();
		a.push_back(x);
	}
}

int ans;

void run() {
	for (int i = 0; i < (1 << k); i++) {
		dist[i] = INF;
	}
	
	queue<int> q;
	for (auto i : a) {
		dist[i] = 0;
		q.push(i);
	}

	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < k; i++) {
			int y = (1 << i) ^ x;
			if (dist[y] != INF) continue;
			dist[y] = dist[x] + 1;
			q.push(y);
		}
	}
/*	cout << "dist = " << endl;
	for (int i = 0; i < (1 << k); i++)
		cout << dist[i] << " ";
	cout << endl;
*/

	ans = 0;
	for (int i = 0; i < (1 << k); i++) {
		if (dist[ans] < dist[i])
			ans = i;
	}
}

string printInt(int x) {
	string ans = "";
	while (k--) {
		ans += '0' + x % 2;
		x /= 2;
	}
	reverse(all(ans));
	return ans;
}

void write() {
	cout << printInt(ans) << endl;
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