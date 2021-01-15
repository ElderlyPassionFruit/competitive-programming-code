#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
	if (n <= 2) {
		cout << "FAIL" << endl;
		exit(0);
	}
}

int ans[3][1010];


bool check(int a, int b) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt += ans[a][i] > ans[b][j];
		}
	}
	//cout << a << " " << b << " " << cnt << endl;
	return cnt * 2 > n * n;
}

bool check() {
	return check(1, 0) && check(2, 1) && check(0, 2);
}

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void run() {
	vector<int> nums;
	for (int i = 1; i <= 3 * n; i++)
		nums.push_back(i);
	while (true) {
		shuffle(nums.begin(), nums.end(), rnd);
		for (int i = 0; i < n; i++)
			ans[0][i] = nums[i], ans[1][i] = nums[i + n], ans[2][i] = nums[i + 2 * n];
		if (check())
			break;
	}	
	//assert(check());
}

void write() {
	cout << "WIN\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
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