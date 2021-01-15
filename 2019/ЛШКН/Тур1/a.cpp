#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;
void read() {
	cin >> n;
	a.resize(n);
	for(auto &i : a) {
		cin >> i;
	}
}

void run() {
	for (auto &i : a) {
		while (i % 2 == 0)
			i /= 2;
		while (i % 3 == 0)
			i /= 3;
	}
	sort(a.begin(), a.end());
}

void write() {
	if (a[0] == a[n - 1])
		cout << "Yes\n";
	else
		cout << "No\n";
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