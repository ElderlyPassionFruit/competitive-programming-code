#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

void run() {
	int cnt1 = 0, cnt2 = 0;
	for (auto i : a)
		if (i % 2 == 0)
			cnt1++;
		else
			cnt2++;
	if (cnt1 && cnt2)
		sort(a.begin(), a.end());
}

void write() {
	for (auto i : a)
		cout << i << " ";
	cout << endl;
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