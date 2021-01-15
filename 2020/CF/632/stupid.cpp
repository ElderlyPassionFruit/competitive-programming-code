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
}

int get(vector<int> have) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (!have[i]) continue;
		for (int j = i + 1; j < n; j++) {
			if (!have[j]) continue;
			chkmax(ans, __gcd(i + 1, j + 1));
		}
	}
	return ans;
}

int get(int cnt) {
	vector<int> have(n, 0);
	for (int i = 0; i < cnt; i++)
		have[i] = 1;
	reverse(all(have));
	int ans = n;
	do {
		chkmin(ans, get(have));
	} while (next_permutation(all(have)));
	return ans;
}

void run() {
	for (int i = 2; i <= n; i++) {
		cout << get(i) << " ";
	}
	cout << endl;
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