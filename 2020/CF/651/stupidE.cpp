#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime> 
#include <bitset>
#include <complex>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;
	{
		int a = 0;
		int b = 0;
		for (auto x : s) {
			a += (x - '0');
		}
		for (auto x : t) {
			b += (x - '0');
		}
		if (a != b) {
			cout << -1 << endl;
			return 0;
		}
	}
	vector<int> v;
	for (int i = 0; i < n; i++) {
		if (s[i] != t[i]) {
			v.push_back(s[i] - '0');
		//	cerr << s[i];
		}
	}
	//cerr << endl;
	int ans = 0;
	vector<int> c(2); 
	for (auto x : v) {
		if (c[x ^ 1] > 0) {
			c[x ^ 1]--;
			c[x]++;
		} else {
			c[x]++;
			ans++;
		}
	}
	cout << ans << endl;
}