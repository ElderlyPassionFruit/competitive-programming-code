#include <bits/stdc++.h>

using namespace std;
#define int long long

#define lnum vector <int>

const int BASE = 26;

lnum read(string s) {
	reverse(s.begin(), s.end());
	int n = s.length();
	lnum ans(n, 0);
	for (int i = 0; i < n; i++) {
		ans[i] = s[i] - 'a';
	}
	return ans;
}

lnum sum(lnum a, lnum b) {
	int n = a.size();
	lnum ans(n + 1, 0);

	for (int i = 0; i < n; i++) {
		ans[i] = ans[i] + a[i] + b[i];
		if (ans[i] >= BASE) {
			ans[i + 1] += ans[i] / BASE;
			ans[i] %= BASE;
		}
	}
	return ans;
}

lnum div2(lnum a) {
	int n = a.size();
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] % 2 == 0)
			a[i] /= 2;
		else {
			a[i - 1] += BASE;
			a[i] /= 2;
		}
	}
	return a;
}

string get(lnum a) {
	string ans = "";
	int n = a.size();
	for (int i = 0; i < n; i++) {
		ans += a[i] + 'a';
	}
	return ans;
}


void read() {
	lnum a, b;
	int n;
	cin >> n;
	string s;
	cin >> s;
	a = read(s);
	cin >> s;
	b = read(s);



	a = sum(a, b);
	a = div2(a);
	
	while (a.size() > n)
		a.pop_back();

	s = get(a);
	reverse(s.begin(), s.end());
	cout << s << endl;
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