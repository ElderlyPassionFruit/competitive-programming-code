#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;
int cnt;

void run() {
	set <int> num;
	for (auto i : a)
		num.insert(i);
	cnt = 0;
	map <int, int> coord;
	for (auto i : num)
		coord[i] = cnt++;
	for (auto &i : a)
		i = coord[i];

	for (int i = 1; i < cnt; i++) {
		vector<int> have(cnt);
		for (int j = 0; j < i; j++)
			have[cnt - 1 - j] = 1;
		do {
			
		} while (next_permutation(have.begin(), have.end())); 
	}
}

void write() {
	cout << cnt - ans << end;
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