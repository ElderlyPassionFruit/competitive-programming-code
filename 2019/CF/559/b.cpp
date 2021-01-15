#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, k;
void read() {
	//cin >> n >> k;
}



string ans;
void run() {
	for (int i = 0; i <= n; i++) {
		string help = "";
		for (int j = 0; j < i; j++)
			help += "0";
		while (help.length() < n)
			help += "1";
		do {
	//		cout << help << " ";
			if (check(help) == k) {
				cout << help << " ";
			}
		} while (next_permutation(help.begin(), help.end()));
	}
	cout << endl;
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//read();
	//cout << cnt("00", "111111100") << endl;
	//cout << check("111111100") << endl;
	//return 0;
	for (n = 13; n <= 14; n++) {
		for (k = n / 2 + 1; k <= n; k++) {
			if (n % 2 != k % 2)
				continue;
			cout << "n = " << n << " k = " << k << endl; 
			run();
		}
	}
	return 0;
	run();
	write();
	return 0;
}