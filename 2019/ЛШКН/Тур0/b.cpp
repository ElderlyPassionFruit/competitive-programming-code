#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int k;

void read() {
	cin >> s >> k;
	//cerr << s << endl << k << endl; 
	k--;
}

char ans;

void run() {
	int n = s.size();
	int cycle = (k / n) % n;
	//cerr << "cycle = " << cycle << endl; 
	s = s + s;
	int pos = k % n;
	//cerr << "pos = " << pos << endl;
	ans = s[cycle + pos];
}

void write() {
	cout << ans << endl;
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