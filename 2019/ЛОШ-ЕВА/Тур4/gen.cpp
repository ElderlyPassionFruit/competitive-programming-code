#include <bits/stdc++.h>

using namespace std;
#define int long long

void gen(int s, int f, int a, int b) {
	int num = s;
	int sum = 0;
	while (num <= f) {
		sum += min(num + a, f + 1) - num;
		num += a + b;
	}
	cout << sum << " ";
}

void read() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, f, a, b;
		cin >> s >> f >> a >> b;
		gen(s, f, a, b);
	}
	cout << endl;
}

void run() {

}

void write() {

}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}