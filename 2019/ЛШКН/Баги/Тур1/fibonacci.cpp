/*
	Fibonacci
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
const ll M2 = MOD * MOD;

struct Matrix {
	vector< vector<ll> > a;
	int n;

	Matrix() : a(), n() {}
	Matrix(int _n) {
		n = _n;
		a.resize(n);
		for (int i = 0; i < n; i++) {
			a[i].resize(n);
			for (int j = 0; j < n; j++)
				a[i][j] = (i == j ? 1 : 0);
		}
	}

	Matrix operator * (const Matrix &A) const {
		if (n != A.n) throw;
		Matrix R = Matrix(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				for (int h = 0; h < n; h++) {
					R.a[i][j] += a[i][h] * A.a[h][j];
					if (R.a[i][j] >= M2) R.a[i][j] -= M2;
				}
				R.a[i][j] %= MOD;
			}
		return R;
	}
};

Matrix bin_pow(Matrix A, ll p) {
	if (p == 0) return Matrix(A.n);
	if (p & 1) return A * bin_pow(A, p - 1);
	return bin_pow(A * A, p / 2);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	Matrix F = Matrix(2);
	F.a[0][0] = 0;
	F.a[0][1] = F.a[1][0] = F.a[1][1] = 1;
	int q;
	scanf("%d", &q);
	while(q--) {
		ll p;
		scanf("%lld", &p);
		Matrix A = bin_pow(F, p);
		printf("%lld\n", A.a[0][1]);
	}

	return 0;
}
