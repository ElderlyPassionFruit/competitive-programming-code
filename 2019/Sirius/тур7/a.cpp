#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
const int MAXN = 1010;
vector <vector <char> > arr;
void read() {
	cin >> n >> m;
	arr.resize(n, vector <char> (m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
}
int ans;


bool check(int i, int j)  {
	if (arr[i][j] == arr[i][(j + 1) % m] && arr[i][j] == arr[(i + 1) % n][j] && arr[i][j] == arr[(i + 1) % n][(j + 1) % m])
		return true;
	return false;	
}

int cnt_all(vector <vector <char> > & arr) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {																																																																																																																																																																																						
			if (check(i, j))
				cnt++;
		}
	}																														
	return cnt;
}

void print() {
	cout << "arr = " << endl;
	for (int x = 0; x < n; x++){
		for (int y = 0; y < m; y++)
			cout << arr[x][y];
		cout << endl;
	}
}

int cnt_h(int j) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (check(i, j)) {
			cnt++;
		}
	}
	return cnt;
}

int cnt_w(int i) {
	int cnt = 0;
	for (int j = 0; j < m; j++) {
		if (check(i, j)) {
			cnt++;
		}
	}
	return cnt;
}

int CNT_H[MAXN], CNT_W[MAXN];
void run() {
	for (int i = 0; i < n; i++)
		CNT_W[i] = cnt_w(i);
	for (int j = 0; j < m; j++)
		CNT_H[j] = cnt_h(j);

	ans = cnt_all(arr);
	int full = 1e9;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int fans = CNT_H[j] + CNT_W[i];
			if (check(i, j))
				fans--;
			full = min(full, fans);
		}
	}
	ans -= full;
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("video.in", "r", stdin);
	freopen("video.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}