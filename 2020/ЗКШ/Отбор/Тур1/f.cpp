#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<string> a;

void read() {
	a.resize(5);
	for (auto &i : a)
		cin >> i;
}

bool check_flash() {
	set<char> x;
	for (auto i : a)
		x.insert(i[1]);
	return x.size() == 1;
}

bool check(char a, char b) {
	if (a == '9' && b == 'T') return true;
	if (a == 'T' && b == 'J') return true;
	if (a == 'J' && b == 'Q') return true;
	if (a == 'Q' && b == 'K') return true;
	if (a == 'K' && b == 'A') return true;
	if (a == 'A' && b == '2') return true;
	if (a >= '2' && a <= '9' && b >= '0' && b <= '9' && b - a == 1) return true;
	return false;
}

map <char, int> have;

bool cmp(string a, string b) {
	char x = a[0];
	char y = b[0];
	for (int i = 2; i <= 9; i++)
		have['0' + i] = i - 2;
	have['T'] = 9;
	have['J'] = 10;
	have['Q'] = 11;
	have['K'] = 12;
	have['A'] = 13;
	return have[x] < have[y];
}

bool check_strait() {
	for (int i = 0; i < 4; i++)
		if (!check(a[i][0], a[i + 1][0]))
			return false;
	return true;
}

void run() {
	sort(all(a), cmp);
	bool f1 = check_flash();
	bool f2 = check_strait();
	vector<string> b = a;
	for (int i = 0; i < 5; i++) {
		a[i] = b[(i - 1 + 5) % 5];
	}
	f2 |= check_strait();
	if (f1 && f2) {
		cout << "straight flush" << "\n";
	} 
	else if (f1) {
		cout << "flush" << "\n";
	}
	else if (f2) {
		cout << "straight" << "\n";
	}
	else {
		cout << "unknown" << "\n";
	}
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