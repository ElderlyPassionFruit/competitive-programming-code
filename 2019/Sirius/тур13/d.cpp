#include <bits/stdc++.h>

using namespace std;
#define int long long

bool check(int x) {
	cout << x << endl;
	string ans;
	cin >> ans;
	return ans == "yes";
}

int rnd() {
	return (rand() << 16) | rand();
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while (true) {
		bool flag = check(1);
		if (flag)
			return 0;
		check(rnd());
	}
	return 0;
}