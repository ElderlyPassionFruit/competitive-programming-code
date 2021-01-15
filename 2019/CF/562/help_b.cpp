#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
void read() {
	cin >> n;
}

bool check(vector<int> a) {
	for (int i = 0; i < n; i++) {
		for (int j = 1; i + 2 * j < n; j++) {
			if (a[i] == a[i + j] && a[i + j] == a[i + j + j])
				return true;
		}
	}
	return false;
}

void run() {
	for (int i = 0; i < n; i++) {
		vector<int> help(n, 0);
		for (int j = 0; j < i; j++)
			help[n - 1 - j] = 1;
		bool flag = true;
		do {
			if (check(help))
				continue;
			flag = false;
			break;
		} while(next_permutation(help.begin(), help.end()));
		
		if (!flag) {
			for (auto j : help)
				cout << j << " ";
			cout << endl;
		}
	}
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