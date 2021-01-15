#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXK = 1e5 + 10;
int arr[MAXK];
int k;
void read() {
	cin >> k;
	for (int i = 0; i < k; i++)
		cin >> arr[i];
}

bool check(int num, int x) {
	while (num) {
		if (num % 10 == x)
			return true;
		num /= 10;
	}
	return false;
}

bool check(int n) {
	for (int i = n; i < n + k; i++) {
		if (!check(i, arr[i - n]))
			return false;
	}
	return true;
}

void run() {
	int i = 1;
	while (true) {
		if (check(i)) {
			cout << i << endl;
			exit(0);
		}
		i++;
	}
}

void write() {

}

signed main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}