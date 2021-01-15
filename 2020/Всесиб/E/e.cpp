#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
	string s;
	getline(cin, s);
}

vector<vector<string>> ans;
mt19937 rnd(time(0));

void run() {
	ans.resize(n);
	for (int i = 0; i < 8; i++) {
		cout << rnd() % 100 << " " << rnd() % 100 << " " << rnd() % 100 << " " << rnd() % 100 << endl;
		for (int i = 0; i < n; i++) {
			string s;
			getline(cin, s);
			if (s == "parallel") continue;
			ans[i].push_back(s);
		}
	}
}

void write() {
	cout << "answer:\n";
	for (auto i : ans)
		cout << i[0] << " " << i[1] << "\n";
	cout.flush();
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