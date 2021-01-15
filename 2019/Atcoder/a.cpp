//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;
#define int unsigned long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int s;
void read() {
	cin >> s;
}

vector<int> a;
void run() {
	int l = sqrt(s);
	if (l * l < s)
		l++;
	int b = l * l - s;
	int x1 = 0, y1 = 0;
	int x2 = l, y3 = l;
	int x3 = b, y2 = 1;

	assert(s == (x2 * y3 - x3 * y2));
	a = {x1, y1, x2, y2, x3, y3};
}

void write() {
	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;
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