#include <bits/stdc++.h>

using namespace std;
#define int long long
int k;
void read() {
	cin >> k;
}
int len(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}
int ans = 0;
void run() {
	int num = 1;
	while (len(num) < k) {
		k -= len(num);
		num++; 
	}
	int l = len(num);
	l -= k;
	for (int i = 0; i < l; i++)
		num /= 10;
	ans = num % 10;
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