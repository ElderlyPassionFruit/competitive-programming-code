#include <bits/stdc++.h>

using namespace std;
#define int long long

void read() {
	int n = 1e5;
	int first = n / 3;
	int last = n - first * 2;
//	freopen("hack.txt", "w", stdout);
	cout << n << endl;
	for (int i = 0; i < first; i++)
		cout << "for 1\n";
	for (int i = 0; i < last; i++)
		cout << "add\n";
	for (int i = 0; i < first; i++)
		cout << "end\n";
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