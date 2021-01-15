#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

void read() {
	string s;
	cin >> s;
	int n = s.size();
	int posL = 0;
	int posR = 0;
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'L') {
			ans[posR + (i - posR) % 2]++; 
		}
		else {
			while (posL <= i || s[posL] != 'L')
				posL++;
			ans[posL - (posL - i) % 2]++;
			posR = i;
		}
	}
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}

void run() {

}

void write() {

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