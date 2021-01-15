#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e10;
const int LLINF = 1e18;
int K[2][2][20];
int pows[10][10];

map <int, int> good_nums;
vector<pair <int, int> > fans;
void f(int l, int r, int num, int cnt, int len) {
	if (num > INF || cnt == 0) return;
	if (r < l) {
		good_nums[num] += cnt;
		return;
	}
	for (int sum = 0; sum <= 18; sum++)
		f(l + 1, r - 1, num + pows[len - 1 - l][len - 1 - r] * sum, cnt * K[l == r][l == 0][sum], len);
}

int make(int x) {
	int ans = 0;
	while (x) {
		ans *= 10;
		ans += x % 10;
		x /= 10;
	}
	return ans;
}

map <int, int> nums;

void stupid_calc(int l, int r) {
	for (int i = l; i <= r; i++) {
		nums[i + make(i)]++;
	}
}

int get_pow(int a, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= a;
	return ans;
}

void calc() {
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			K[0][0][i + j]++;

	for (int i = 0; i <= 9; i++)
		K[1][0][i] = 1;
	
	for (int i = 1; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			K[0][1][i + j]++;
	
	for (int i = 1; i <= 9; i++)
		K[1][1][i] = 1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			pows[i][j] = get_pow(10LL, i) + get_pow(10LL, j);
		}
	}
	
	for (int i = 1; i <= 10; i++) {
		f(0, i - 1, 0, 1, i);
	}

	for (auto i : good_nums) {
		int x = i.first + make(i.first);
		if (x <= INF)
		good_nums[x] += i.second; 
	}

	fans.push_back({0, 0});
	for (auto i : good_nums) {
		fans.push_back({i.first, fans.back().second + i.second});
	}
}


int solve(int r) {
	auto cnt = *(--upper_bound(fans.begin(), fans.end(), make_pair(r, LLINF)));
	return cnt.second + r;
}

int solve(int l, int r) {
	return solve(r) - solve(l - 1);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	calc();
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << solve(l, r) << "\n";
	}
	return 0;
}