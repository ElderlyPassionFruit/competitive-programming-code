#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,m;
	cin>>n>>m;
	int fs = n*(n-1) / 2;
	int ss = (m-1) *(m-2) / 2;
	int tx = max(m-n, 0ll);
	tx--;
	ss -= tx*(tx+1) / 2;
	int ty = max(n- m, 0ll);
	fs-= ty*(ty+1)/2;
	cout<<fs+ss;
	return 0;
}