#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> a;
void read() {
	cin >> n;
	n *= 2;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
	int sum1 = 0;
	for (int i = 0; i < n / 2; i++)
		sum1 += a[i];
	int sum2 = 0;
	for (int i = n / 2; i < n; i++)
		sum2 += a[i];
	if (sum1 == sum2) {
		cout << -1 << endl;
		return;
	}
	else {
		for (auto i : a)
			cout << i << " ";
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