#include <bits/stdc++.h>

using namespace std;
#define int long long


string s;
void read() {
	cin >> s;
	if (s == "a") cout << 0 << endl << s;
	if (s == "b") cout << 0 << endl << s;

	if (s == "aa") cout << 0 << endl << s;
	if (s == "ab") cout << 1 << endl << "aba";
	if (s == "ba") cout << 1 << endl << "bab";
	if (s == "bb") cout << 0 << endl << s;

	if (s == "aaa") cout << 0 << endl << s;
	if (s == "aab") cout << 1 << endl << "baab";
	if (s == "aba") cout << 0 << endl << s;
	if (s == "abb") cout << 1 << endl << "abba";
	if (s == "baa") cout << 1 << endl << "baab";
	if (s == "bab") cout << 0 << endl << s;
	if (s == "bba") cout << 1 << endl << "abba";
	if (s == "bbb") cout << 0 << endl << s;


	if (s == "aaaa") cout << 0 << endl << s;
	if (s == "aaab") cout << 1 << endl << "baaab";
	if (s == "aaba") cout << 1 << endl << "ababa";
	if (s == "aabb") cout << 2 << endl << "aabbaa";
	if (s == "abaa") cout << 1 << endl << "ababa";
	if (s == "abab") cout << 1 << endl << "ababa";
	if (s == "abba") cout << 0 << endl << "abba";
	if (s == "abbb") cout << 1 << endl << "abbba";


	if (s == "baaa") cout << 1 << endl << "baaab";
	if (s == "baab") cout << 0 << endl << "baab";
	if (s == "baba") cout << 1 << endl << "babab";
	if (s == "babb") cout << 1 << endl << "babab";
	if (s == "bbaa") cout << 2 << endl << "aabbaa";
	if (s == "bbab") cout << 1 << endl << "bbabb";
	if (s == "bbba") cout << 1 << endl << "abbba";
	if (s == "bbbb") cout << 0 << endl << s;
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