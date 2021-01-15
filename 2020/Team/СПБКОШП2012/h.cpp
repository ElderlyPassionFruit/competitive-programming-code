#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

void solve(string s) {
	//cout << s << endl;
	int cnt = 0;
	for (auto i : s) {
		if (i >= 'a' && i <= 'z') break;
		cnt++;
	}
	//cout << s << " " << cnt << endl;
	reverse(s.begin(), s.end());
	//cout << s << " " << cnt << endl;
	cnt *= 2;
	while(cnt--)
		s.pop_back();
	//cout << s << " " << cnt << endl;
	//return;
	cnt = 0;
	for (auto i : s) {
		if (i >= 'a' && i <= 'z') break;
		cnt++;
	}
	reverse(s.begin(), s.end());
	//cout << s << " " << cnt << endl;
	cnt *= 2;
	while (cnt--)
		s.pop_back();
	cout << s;	
} 

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("rebus.in", "r", stdin);
	freopen("rebus.out", "w", stdout);
	string s;
	while (cin >> s) {
		solve(s);
	}
	return 0;
}