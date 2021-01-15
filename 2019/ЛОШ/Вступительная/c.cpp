#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector <int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

void run() {
	sort(a.begin(), a.end());	
}

void write() {
	cout << a[0] << " " << a[1] << endl;
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