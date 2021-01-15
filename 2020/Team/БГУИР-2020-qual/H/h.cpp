#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int n, m;

vector <int> make(vector <int> a) {
	vector <int> fans;
	for (int i = 0; i < a.size(); i++) {
		int j;
		for (j = i; j < a.size(); j++) {
			if (a[i] != a[j])
				break;
		}
		j--;
		fans.push_back(j - i + 1);
		fans.push_back(a[i]);
		i = j;
	}
	vector <int> ans = fans;
	if (fans.size() > 1e5) {
		ans = {};
		for (int i = fans.size() - 1e5; i < fans.size(); i++)
			ans.push_back(fans[i]);
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	n--;
	vector <int> a;
	a = {1};
	set <int> fhesh;
	vector <int> hes;
	for (int i = 0; i < min(300LL, n); i++) {
		a = make(a);
	}
	n -= min(300LL, n);
	n %= 4;
	for (int i = 0; i < n; i++) {
		a = make(a);
	}
	for (int i = max((int)a.size() - m, 0LL); i < a.size(); i++)
		cout << a[i];
	cout << endl;
	return 0;
}