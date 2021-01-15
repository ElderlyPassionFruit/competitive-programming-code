#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
const int MAXN = 1e7 + 228 + 1337;
vector<int> pr;
int fans[MAXN];
int mx[MAXN];
int n, q;
const int INF = 1e9 + 228 + 1337;

void read() {
	cin >> n >> q;
	pr.resize(n);
	for (auto &i : pr) {
		cin >> i;
	}
	sort(all(pr));
}

void build() {
	fill(mx, mx + MAXN, 0);
	for (auto i : pr) {
		for (int j = 0; j < MAXN; j += i) {
			chkmax(mx[j], i);
		}
	}
	int posR = pr.back();
	int posL = 1;
	fill(fans, fans + MAXN, INF);
	fans[0] = 0;
	//cout << "puhh" << endl;
	for (int jumps = 1; jumps < MAXN; jumps++) {
		int pos = posL;
		while (posL < MAXN && posL < posR) {
			fans[posL] = jumps;
			chkmax(pos, posL + mx[posL]);
			posL++;
		}
		if (pos == posR) break;
		posR = pos;
	}
	/*cout << "fans = " << endl;
	for (int i = 0; i < 10; i++) {
		cout << fans[i] << " ";
	}
	cout << endl;*/
}

int get(int x) {
	return fans[x];
}

vector<int> ans;

void run() {
	build();

	while (q--) {
		int x;
		cin >> x;
		ans.push_back(get(x));
	}
}

void write() {
	for (auto i : ans) {
		if (i == INF) {
			cout << "oo\n";
		} else {
			cout << i << "\n";
		}
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