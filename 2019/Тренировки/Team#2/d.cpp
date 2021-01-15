#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(pair <int, int> p) {
	return max(abs(p.first), abs(p.second));
}
 
int n;
vector<pair <int, int> > a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		pair <int, int> x;
		cin >> x.first >> x.second;
		a[i] = {get(x), i};
	}
}

vector<int> ans;

void run() {
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		if (a[i].first <= i) {
			cout << -1 << endl;
			exit(0);
		}
		ans.push_back(a[i].second + 1);
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