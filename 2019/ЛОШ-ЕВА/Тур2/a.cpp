#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> a, b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a){
		cin >> i;
		i--;
	}
	b.resize(n);
	for (auto &i : b){
		cin >> i;
		i--;
	}
}

int ans;

void run() {
	vector<int> pos(n);
	for (int i = 0; i < n; i++) {
		pos[b[i]] = i;
	}

	ans = 1;
	for (int i = 0; i < n - 1; i++) {
		if (pos[a[i + 1]] - pos[a[i]] == 1)
			continue;
		ans++;
	}

}

void write() {
	cout << ans << endl;
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