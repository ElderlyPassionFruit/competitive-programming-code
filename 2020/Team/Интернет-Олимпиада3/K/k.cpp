#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void no() {
	cout << "Impossible";
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	map<char, int> have;
	for (auto i : s) {
		if (i == '<')
			cnt1++;
		else if (i == '>')
			cnt2++;
		else if (i == '/')
			cnt3++;
		else
			have[i]++;
	}
	if (cnt1 != cnt2 || cnt1 != cnt3 * 2 || cnt2 != cnt3 * 2)
		no();
	if (cnt1 % 2) no();
	int sum = 0;
	for (auto i : have) {
		if (i.second % 2 != 0) no();
		sum += i.second;
	}
	if (sum < cnt1) no();
	while (cnt1 > 2) {
		cout << "<";
		char x = '-';
		for (auto i : have) {
			if (i.second != 0) {
				x = i.first;
				have[x] -= 2;
				break;
			}
		}
		assert(x != '-');
		cout << x;
		cout << ">";
		cout << "</";
		cout << x;
		cout << ">";
		cnt1 -= 2;
	}
	cout << "<";
	for (auto i : have) {
		for (int j = 0; j < i.second / 2; j++) {
			cout << i.first;
		}
	}
	cout << ">";
	cout << "</";
	for (auto i : have) {
		for (int j = 0; j < i.second / 2; j++) {
			cout << i.first;
		}
	}
	cout << ">";
	return 0;
}