#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
char arr[510][510];
int sum = 0;

bool check(int x, int y) {
	if (arr[x][y] != '*')
		return 0;
	int cnt = 1;
	
	if (arr[x - 1][y] != '*' || arr[x + 1][y] != '*' || arr[x][y + 1] != '*' || arr[x][y - 1] != '*')
		return 0;

	for (int i = x + 1; i <= n; i++) {
		if (arr[i][y] != '*')
			break;
		cnt++;
	}

	for (int i = x - 1; i >= 1; i--) {
		if (arr[i][y] != '*')
			break;
		cnt++;
	}

	for (int i = y + 1; i <= m; i++) {
		if (arr[x][i] != '*')
			break;
		cnt++;
	}

	for (int i = y - 1; i >= 1; i--) {
		if (arr[x][i] != '*')
			break;
		cnt++;
	}

	return cnt == sum;
}


void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> arr[i][j];
			sum += arr[i][j] == '*';
		}
	}

	//cout << sum << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (check(i, j)) {
				cout << "YES" << endl;
				return;
			}
		}
	}
	cout << "NO" << endl;
	return;
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