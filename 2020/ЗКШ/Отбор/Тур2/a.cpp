#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

int a, b, c, d;
void read() {
	cin >> a >> b >> c >> d;
}

vector<vector<int> > ans1;

void run() {
	int a1 = a, b1 = b, c1 = c, d1 = d;
	int sum = 0;
	ans1.assign(3, vector<int> (3, 0));
	ans1[0][0] = min(a, b);
	int x = min(a, b);
	sum += x;
	a -= x;
	b -= x;
	ans1[0][2] = min(a, c);
	x = min(a, c);
	sum += x;
	a -= x;
	c -= x;
	ans1[0][1] = a;
	sum += a;
	ans1[2][0] = min(b, d);
	x = min(b, d);
	sum += x;
	b -= x;
	d -= x;
	ans1[1][0] = b;
	sum += b;
	ans1[2][2] = min(c, d);
	x = min(c, d);
	sum += x;
	c -= x;
	d -= x;
	ans1[2][1] = d;
	sum += d;
	ans1[1][2] = c;
	sum += c;
	cout << sum << "\n";
	for (auto i : ans1) {
		for (auto j : i)
			cout << j << " ";
		cout << "\n"; 
	}
	cout << a1 + b1 + c1 + d1 << endl;
	cout << "0 " << a1 << " 0" << endl;
	cout << b1 << " 0 " << c1 << endl;
	cout << "0 " << d1 << " 0" << endl;
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