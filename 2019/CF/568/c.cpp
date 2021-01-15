#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<int> t;

void read() {
	cin >> n >> m;
	t.resize(n);
	for (auto &i : t)
		cin >> i;
}
vector<int> ans;
void run() {
	map <int, int> help;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int fans = 0;
		int sum_now = sum;
		for (auto j : help) {
			if (sum_now + t[i] > m) {
				if (sum_now + j.first * j.second + t[i] > m) {
					fans += j.second;
					sum_now += j.first * j.second;
				}
				else {
					//sum_now - j.first * x + t[i] <= m
					int x = (sum_now - m + t[i] + (-j.first) - 1) / (-j.first);
					fans += x;
					break;
				}
			}
			else {
				break;
			}
		}

		sum += t[i];
		help[-t[i]]++;
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
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