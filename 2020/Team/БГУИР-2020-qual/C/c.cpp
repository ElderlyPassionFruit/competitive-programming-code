#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		int a, b;
		cin >> a >> b;
  	  	for (int c = 1; c <= 50; c++) {
    		if (a + b != c) {
    			cout << c << endl;
    			break;
    		}
    	}
  	}
	return 0;
}