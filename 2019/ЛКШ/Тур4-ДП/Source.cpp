#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <tuple>
#include <cmath>
#include <functional>
#include <cassert>
#include <algorithm>
#include <set>
#include <deque>
#include <numeric>
using namespace std;
#define kekek ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)	

int n, k;
const long long inf = 1e13 + 1337;
vector<vector<pair<int, long long>>> g;

bool operator <(pair<long long, int>& a, pair<long long, int>& b) {
	if (a.first != b.first) return a.first < b.first;
	return a.second < b.second;
}

pair<long long, int> dp(long long lambda) {
	vector<pair<long long, int>> with(n + 1), out(n + 1), save(n + 1);	// save[i] = max(with[i], out[i])
	for (int i = n; i > 0; i--) {
		long long sum1 = 0;
		int sum2 = 0;
		for (auto u : g[i]) {
			if (out[u.first] < with[u.first]) {
				save[u.first] = with[u.first];
			}
			else {
				save[u.first] = out[u.first];
			}
			sum1 += save[u.first].first;
			sum2 += save[u.first].second;
		}

		if (out[i] < make_pair(sum1, sum2)) {
			out[i] = { sum1, sum2 };
		}

		for (auto u : g[i]) {
			long long now1 = sum1 - save[u.first].first + out[u.first].first + u.second + lambda;
			int now2 = sum2 - save[u.first].second + out[u.first].second + 1;

			if (with[i] < make_pair(now1, now2)) {
				with[i] = { now1, now2 };
			}
		}
	}

	if (out[1] < with[1]) {
		return with[1];
	}
	else {
		return out[1];
	}
}

bool check(long long lambda) {
	auto f = dp(lambda);
	return f.second < k;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	kekek;
	cin >> n >> k;
	g.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		long long c;
		cin >> a >> b >> c;
		if (a > b) swap(a, b);
		g[a].push_back({ b, c });
	}

	if (check(inf)) return cout << "Impossible" << endl, 0;

	long long l = -inf, r = inf;
	while (r - l > 1) {
		long long m = (l + r) / 2;
		if (check(m)) {
			l = m;
		}
		else {
			r = m;
		}
	}

	cout << dp(r).first - r * k << endl;
	
//	system("pause");
	return 0;
}