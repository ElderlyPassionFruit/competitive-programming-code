/*
	SQRT-decomposition
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
#define mp make_pair
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 100100;
const int B = 300;
const int SZ = N / B + 2;
ll a[N];
ll blockSum[SZ];

void setInPoint(int p, ll x) {
	int id = p / B;
	blockSum[id] -= a[p];
	a[p] = x;
	blockSum[id] += a[p];
}
ll getSum(int l, int r) {
	int lId = l / B, rId = r / B;
	ll sum = 0;
	for (int i = l; i / B == lId; i++)
		sum += a[i];
	for (int i = r - 1; i / B == rId; i--)
		sum += a[i];
	for (int id = lId + 1; id < rId; id++)
		sum += blockSum[id];
	return sum;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++) {
		ll x;
		scanf("%lld", &x);
		setInPoint(i, x);
	}
	while(q--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int p;
			ll x;
			scanf("%d%lld", &p, &x);
			p--;
			setInPoint(p, x);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			l--;
			printf("%lld\n", getSum(l, r));
		}
	}

	return 0;
}
