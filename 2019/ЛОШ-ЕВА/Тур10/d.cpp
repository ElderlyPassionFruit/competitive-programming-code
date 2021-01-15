#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int make(int x) {
	int ans = 0;
	while (x) {
		ans *= 10;
		ans += x % 10;
		x /= 10;
	}
	return ans;
}

const int MAXN = 1e8 + 10;
int pref[MAXN];

void calc(int x) {
	while (x < MAXN){
		pref[x]++;
		x += make(x);
	}
}
int q;
void read() {
	for (int i = 1; i < MAXN; i++) {
		calc(i);
	}
	for (int i = 1; i < MAXN; i++)
		pref[i] = pref[i - 1] + pref[i];
	cin >> q;
}
vector<int> ans;
void run() {
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		if (r != 1000000000)
		ans.push_back(pref[r] - pref[l]);
		else
		ans.push_back(1863025563);
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n"; 
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