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
#include <random>
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2;
const int K = 2;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n = rng() % N + 3;
	cout << n << endl;
	vector<pair<int, int>> ed;
	for (int i = 1; i < n; i++) {
		ed.push_back({(rng() % i) + 1, i + 1});
	}
	shuffle(ed.begin(), ed.end(), rng);
	set<pair<int, int>> st;
	for (auto [f, s] : ed) {
		if (f > s) swap(f, s);
		st.insert({f, s});
		//st.insert({s, f});
		cout << f << ' ' << s << ' ' << rng() % K + 1 << endl;
	}
	int u = rng() % (n - 1) + 1;
	int v = rng() % u;
	while (st.count({v + 1, u + 1})) {
		u = rng() % (n - 1) + 1;
		v = rng() % u;
	}
	cout << u + 1 << ' ' << v + 1 << ' ' << rng() % K + 1 << endl;
}