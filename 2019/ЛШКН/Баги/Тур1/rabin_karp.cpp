/*
	Polynomial hashing
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

const ll MOD = (ll)998244353;
const ll P = 37;
ll add(ll x, ll y) {
	x += y;
	if (x >= MOD) return x - MOD;
	return x;
}
ll sub(ll x, ll y) {
	x -= y;
	if (x < 0) return x + MOD;
	return x;
}
ll mult(ll x, ll y) {
	return (x * y) % MOD;
}

const int N = 100100;
char s[N], p[N];

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%s", s);
	scanf("%s", p);
	ll H = 0;
	for (int i = 0; i < (int)strlen(p); i++)
		H = add(mult(H, P), (int)(p[i] - 'a'));
	ll HP = 1;
	for (int i = 0; i < (int)strlen(p) - 1; i++)
		HP = mult(HP, H);
	ll H2 = 0;
	int ans = 0;
	for (int i = 0; i < (int)strlen(s); i++) {
		H2 = add(mult(H2, P), (int)(s[i] - 'a'));
		if (i >= (int)strlen(p) - 1) {
			if (H == H2) ans++;
			H2 = sub(H2, mult((int)(s[i - (int)strlen(p) + 1] - 'a'), HP));
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
