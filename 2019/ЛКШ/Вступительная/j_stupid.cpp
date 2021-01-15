#include <bits/stdc++.h>

using namespace std;
#define int long long

set <vector <int> > get(int k, int len, int max_len, vector <int> have) {
	if (len == max_len - 1) {
		set <vector <int> > ans;
		for (int i = 1; i <= k; i++) {
			have.push_back(i);
			ans.insert(have);
			have.pop_back();
		}
		return ans;
	}
	set <vector <int> > ans;
	for (int i = 1; i <= k; i++) {
		have.push_back(i);
		auto x = get(k, len + 1, max_len, have);
		have.pop_back();
		for (auto j : x) 
			ans.insert(j);
	}
	return ans;
}

int check(const vector <int> & a) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] == a[(i + 1) % n])
			return 0;
	}
	return 1;
}

int f(int n, int k) {
	auto p = get(k, 0, n, {});
	int ans = 0;
	for (auto i : p) {
		if (check(i)) {
			ans++;
		}
	}
	return ans;
}


void read() {
	int n;
	cin >> n;
	for (int i = 0; i < 20; i++) {
		cout << f(n, i) << endl;
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