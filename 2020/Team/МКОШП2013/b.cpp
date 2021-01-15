#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

int l, r;
bool flag = true;

void make(int sz, char x) {
	if (flag) {
		sz++;
		flag = false;
	}
	if (x == '>') {
		for (int i = l + sz - 1; i >= l; i--)
			cout << i << " ";
		l += sz;
	}
	else {
		for (int i = r - sz + 1; i <= r; i++)
			cout << i << " ";
		r -= sz;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	string s;
	cin >> s;
	l = 1, r = n;
	for (int i = 0; i < n - 1; i++) {
		int j = i;
		while (j < n - 1 && s[j] == s[i])
			j++;
		//cout << i << " " << j << endl;
		make(j - i, s[i]);
		//cout << endl;
		//cout << "l = " << l << " r = " << r << endl;
		//cout << endl;
		i = j - 1;
	}
	cout << endl;
	return 0;
}