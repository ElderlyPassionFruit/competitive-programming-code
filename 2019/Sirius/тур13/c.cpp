#include <bits/stdc++.h>

using namespace std;
#define int long long

bool cmp(int a, int b) {
	cout << "? " << a << " " << b << endl;
	char x;
	cin >> x;
	return x == '<';
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector <int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
	}
	random_shuffle(a.begin(), a.end());
	
	partial_sort(a.begin(), a.begin() + k, a.end(), cmp);
	cout << "! ";
	for (int i = 0; i < k; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}