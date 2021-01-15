#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n1, n2, n12;
    cin >> n1 >> n2 >> n12;
    cout << (n1 + 1) * (n2 + 1) / (n12 + 1) - 1 << endl;
	return 0;
}