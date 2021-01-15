#include <bits/stdc++.h>

using namespace std;
#define int long long
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
	if (fans.size() > 1e4) {
		ans = {};
		for (int i = fans.size() - 1e4; i < fans.size(); i++)
			ans.push_back(fans[i]);
	}
	for (auto i : ans) {
		if (i > 3) {
			cout << i << endl;
		}
	}
	return ans;
}

void read() {
	cin >> n >> m;
	vector <int> a;
	a = {1};
	set <int> fhesh;
	vector <int> hes;
	for (int i = 0; i < n; i++) {
		a = make(a);
		cout << i + 2 << " ";
		for (int i = max(0LL, (int) a.size() - m); i < a.size(); i++)
			cout << a[i];
		cout << endl;
	}
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();	
	write();
	return 0;
}