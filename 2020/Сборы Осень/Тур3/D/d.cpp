#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<char> out = {'U', 'L'};
mt19937 rnd(time(0));

bool random_query() {
	cout << out[rnd() % 2] << endl;
	char ans;
	cin >> ans;
	return ans == 'N';
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (random_query()) {

	}
	return 0;
}