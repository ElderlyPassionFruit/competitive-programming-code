/*
	Segment Tree
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

struct Node {
	int l, r;
	ll sum;

	Node() : l(), r(), sum() {}
	Node(int _l, int _r) : l(_l), r(_r), sum(0) {}
};
const int N = 1 << 17;
Node tree[2 * N + 5];

void build() {
	for (int i = 0; i < N; i++)
		tree[N + i] = Node(i, i + 1);
	for (int i = N - 1; i > 0; i--)
		tree[i] = Node(tree[2 * i].l, tree[2 * i + 1].r);
}
void setInPoint(int p, ll x) {
	p += N;
	tree[p].sum = x;
	while(p > 1) {
		p >>= 1;
		tree[p].sum = tree[2 * p].sum + tree[2 * p + 1].sum;
	}
}
ll getSum(int v, int l, int r) {
	if (l <= tree[v].l && tree[v].r <= r)
		return tree[v].sum;
	if (l >= tree[v].r || tree[v].l >= r)
		return 0;
	return getSum(2 * v, l, r) + getSum(2 * v + 1, l, r);
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
			printf("%lld\n", getSum(1, l, r));
		}
	}

	return 0;
}
