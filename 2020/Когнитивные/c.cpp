#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;
void read() {
	cin >> s;
	n = s.size();
}

vector<string> ans;

bool cmp(string & a, string & b) {
	map<string, int> have;
	have["A"] = 0;
	have["K"] = 1;
	have["Q"] = 2;
	have["J"] = 3;
	have["10"] = 4;
	have["9"] = 5;
	have["8"] = 6;
	have["7"] = 7;
	have["6"] = 8;
	have["5"] = 9;
	have["4"] = 10;
	have["3"] = 11;
	have["2"] = 12;
	return have[a] < have[b];
}

string suka(char x) {
	string ans = "";
	ans += x;
	return ans;
}

void run() {
	for (int i = 0; i < n; i++) {
		if (s[i] != '1')
			ans.push_back(suka(s[i]));
		else if (i + 1 < n && s[i + 1] == '0') 
			ans.push_back("10"), i++;
	}
	sort(all(ans), cmp);
}

void write() {
	for (auto i : ans)
		cout << i;
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