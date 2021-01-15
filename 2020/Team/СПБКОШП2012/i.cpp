#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)(x).begin(),(x).end()

vector<int> perm;
int getnum(const string & s) {
	int sz = s.size();
	if(perm[s[0] - 'a'] == 0 && sz != 1) {
		return -228;
	}
	int num = 0;
	for(int i = 0; i < sz; i++) {
		num *= 10;
		num += perm[s[i] -'a'];
	}
	return num;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("tiv.in","r",stdin);
	freopen("tiv.out","w",stdout);
	int n;
	cin>>n;
	vector<string> a(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	perm.resize(10);
	iota(all(perm), 0);
	do {
		int x = -1;
		bool f = true;
		for (auto &i : a) {
			int y = getnum(i);
			if (x >= y) {
				f = false;
				break;
			}
			x = y;
		}
		if (!f) continue;
		//for (auto &i : a)
		//	cout << getnum(i) << endl;
		cout << "Yes" << endl;
		for (auto i : perm)
			cout << i << " ";
		cout << endl;
		return 0;
	}while(next_permutation(all(perm)));
	cout<<"No";
	return 0;
}