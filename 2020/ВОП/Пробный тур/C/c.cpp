#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int query(int x) {
	cout << x << endl;
	int ans;
	cin >> ans;
	if (!ans) exit(0);
	return ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int r;
    cin >> r;
    r++;
    int l = 0;
    while (l < r - 1) {
    	int mid = (l + r) / 2;
    	if (query(mid) < 0)
    		r = mid;
    	else
    		l = mid;
    }
    assert(false);
    return 0;
}