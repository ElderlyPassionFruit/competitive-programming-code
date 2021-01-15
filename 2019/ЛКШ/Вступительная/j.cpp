#pragma GCC optimize("Ofast,no-stack-protector")

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

#ifdef FAST_ALLOCATOR_MEMORY
	int allocator_pos = 0;
	char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
	inline void * operator new ( size_t n ) {
		char *res = allocator_memory + allocator_pos;
		allocator_pos += n;
		assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
		return (void *)res;
	}
	inline void operator delete ( void * ) noexcept { }
#endif

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;
pair <int, int> g[2 * MAXN], q[MAXN];
int pos_start[MAXN], pows[MAXN], pows2[MAXN];
int n, k;
int fact[MAXN], refact[MAXN];

int mul(int a, int b) {
	return ((long long) a * b) % MOD;
}

int binpow(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 0) {
		int x = binpow(a, n / 2);
		return mul(x, x);
	}
	else {
		int x = binpow(a, n - 1);
		return mul(a, x);
	}
}

int DIV(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

int mod(int n) {
    if (n < 0)
        n += MOD;
    if (n >= MOD)
        n -= MOD;
    return n;
}

void make() {
	fact[0] = 1;
	refact[0] = DIV(1, 1);
	for (int i = 1; i < MAXN; i++) {
		fact[i] = (long long) fact[i - 1] * i % MOD;
		refact[i] = DIV(1, fact[i]);
	}
	pows[0] = 1, pows2[0] = 1;
	for (int i = 1; i < MAXN; i++) {
	    pows[i] = (long long)pows[i - 1] * k % MOD;
	    pows2[i] = (long long)pows2[i - 1] * (k - 1) % MOD;
	}
}

int c_n_k(int n, int k) {
	return mul(fact[n], mul(refact[n - k], refact[k]));
}

vector <int> h = {1, -1};
int get_ans(int c1, int c2) {
	if (c2 == 0) {
		return mul(k, pows2[c1 - 1]);
	}
	
	long long ans = pows2[c1 - c2];	
	long long fans = 0;
	for (int i = 0; i <= c2 - 2; i++) {
		fans += 1LL * h[i % 2] * pows[c2 - i] * c_n_k(c2, i) % MOD;
		fans = mod(fans);
	}
	fans += 1LL * h[(c2 - 1) % 2] * k * (c2 - 1) % MOD;
	fans = mod(fans);

	ans = mul(ans, fans);
	return ans;
}

int ed = 0;

void read() {
	scanf("%i", &n);
	scanf("%i", &k);
	make();
	for (int i = 0; i < n; i++) {
		int p;
		scanf("%i", &p);
		p--;
		if (p == i)
			continue;
	    g[ed++] = {i, p};
	    g[ed++] = {p, i};
	}
	sort(g, g + ed);
	int last = -1;
	for (int i = 0; i < ed; i++) {
		if (g[i].first != last)
			pos_start[g[i].first] = i;
		last = g[i].first;
	}
}

int pred[MAXN];

int cnt, cnt_full;
bool flag;
const int INF = -1e9;

int pos_in_q;

void bfs(int v) {
    pos_in_q = 0;
    q[pos_in_q] = {v, -10};
    
	while (pos_in_q >= 0) {
		auto x = q[pos_in_q];
		pos_in_q--;
		
		if (pred[x.first] != -1)
			continue;
		cnt_full++;
		int v = x.first;
		int p = x.second;

		pred[v] = p;
		pair <int, int> last = make_pair(v, INF);
		int ind = pos_start[v];
	
		for (int pos = ind; pos < ed; pos++) {	
			if (g[pos].first != v)
				break;
			if (g[pos] == last)
				continue;
			last = g[pos];
			int i = g[pos].second;

			if (i == p)
				continue;

			if (pred[i] == -1) {
				q[++pos_in_q] = {i, v};
			}
			else {
				if (!flag) {
					flag = true;
					cnt = 1;
					int u = v;
					while (u != i && pred[u] != -10) {
						u = pred[u];
						cnt++;
					}
				}
			}
		}
	}
} 

long long ans;
void run() {
    for (int i = 0; i < MAXN; i++)
    	pred[i] = -1;
	
	ans = 1;
	for (int i = 0; i < n; i++) {
		if (pred[i] == -1) {
			cnt = 0;
			cnt_full = 0;
			flag = false;
			bfs(i);
			ans = ans * get_ans(cnt_full, cnt) % MOD;
		}
	}
}

void write() {
	int fans = ans;
	printf("%i", fans);
}

signed main() {
	read();
	run();
	write();
	return 0;
}