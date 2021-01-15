#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, t;
const int MAXN = 2e5 + 10;
const int B = 500;
vector<int> a[B];
int ans[MAXN];

vector<pair<int, int>> have;

void read() {
	cin >> n >> t;
	have.resize(n);
	for (auto &i : have) {
		cin >> i.first >> i.second;
		i.first--;
	}
}

int now[MAXN];

void run() {
	for (auto i : have) {
		if (i.second >= B) {
			int pos = i.first;
			while (pos < t) {
				ans[pos]++;
				pos += i.second;
			}
		} else {
			a[i.second].push_back(i.first);
		}
	}
	for (int i = 1; i < B; i++) {
		sort(all(a[i]));
		int pos = 0;
		for (int j = 0; j < t; j++) {
			while (pos < a[i].size() && a[i][pos] == j) {
				now[j]++;
				pos++;
			}
			ans[j] += now[j];
			if (j + i < t) {
				now[j + i] += now[j];
			}
		}
		for (int j = 0; j < t; j++)
			now[j] = 0;
	} 
}

void write() {
	for (int i = 0; i < t; i++)
		cout << ans[i] << " ";
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