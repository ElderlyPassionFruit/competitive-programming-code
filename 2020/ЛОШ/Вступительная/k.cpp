#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 64*1024*1024
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int) FAST_ALLOCATOR_MEMORY];
 
inline void *operator new(size_t n) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int) FAST_ALLOCATOR_MEMORY);
    return (void *) res;
}
 
inline void operator delete(void *) noexcept {}
 
inline void operator delete(void *, size_t) {}
#endif

static const int buf_size = 4096;
 
static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;
 
inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0;
        buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len)
            return 1;
    }
    return 0;
}
 
inline int getChar() {
    return isEof() ? -1 : buf[buf_pos++];
}
 
inline int peekChar() {
    return isEof() ? -1 : buf[buf_pos];
}
 
inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32)
        c = getChar();
    return c;
}
  
template<class T = int>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-') {
        s = -1;
        c = getChar();
    } else if (c == '+')
        c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

const int MAXN = 2e3 + 10;
const int MAXLOG = 11;
int n;
vector<int> gr[MAXN];
int Tin[MAXN];
vector<int> g[MAXN];

int tin[MAXN][MAXN], tout[MAXN][MAXN], rtin[MAXN][MAXN], timer;
int h[MAXN][MAXN], par[MAXN][MAXN];
vector<pair<int, int>> q[MAXN];

int lg[MAXN];
int sparse[MAXN][MAXN][MAXLOG];

bitset<MAXN> dp[MAXN];
int ans;

void read() {
	n = readInt();
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		u = readInt();
		v = readInt();
		u--;
		v--;
		gr[u].push_back(v);
		gr[v].push_back(u);
	}
}

void dfs(int v, int p, int root) {
	tin[root][v] = timer;
	rtin[root][tin[root][v]] = v;
	timer++;
	par[root][v] = p;
	if (v != root && root < v) {
		q[h[root][v]].push_back({root, v});
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		h[root][i] = h[root][v] + 1;
		dfs(i, v, root);
	}
	tout[root][v] = timer - 1;
}

void build(int root) {
	for (int i = 0; i < n; i++) {
		sparse[root][i][0] = h[root][rtin[root][i]];
	}
	for (int l = 1; l < MAXLOG; l++) {
		for (int i = 0; i + (1 << l) <= n; i++) {
			sparse[root][i][l] = max(sparse[root][i][l - 1], sparse[root][i + (1 << (l - 1))][l - 1]);
		}
	}
}

int get_max(int l, int r, int root) {
	if (l > r) return 0;
	int log = lg[r - l];
	return max(sparse[root][l][log], sparse[root][r - (1 << log) + 1][log]);
}

void build() {
	lg[0] = lg[1] = 0;
	for (int i = 2; i < n; i++) {
		lg[i] = lg[i / 2] + 1;
	}
	for (int root = 0; root < n; root++) {
		timer = 0;
		h[root][root] = 0;
		dfs(root, -1, root);
		build(root);
	}
}

int get(int root, int ban1, int ban2 = -1) {
	if (ban2 == -1) {
		int ans = 0;
		chkmax(ans, get_max(0, tin[root][ban1] - 1, root));
		chkmax(ans, get_max(tout[root][ban1] + 1, n - 1, root));
		return ans;
	} else {
		if (tin[root][ban1] > tin[root][ban2]) swap(ban1, ban2);
		int ans = 0;
		chkmax(ans, get_max(0, tin[root][ban1] - 1, root));
		chkmax(ans, get_max(tout[root][ban1] + 1, tin[root][ban2] - 1, root));
		chkmax(ans, get_max(tout[root][ban2] + 1, n - 1, root));
		return ans;
	}
}

bool get_dp(int a, int b) {
	int nxtA = par[b][a];
	int nxtB = par[a][b];
	int haveA, haveB;
	haveA = get(nxtA, a, par[b][nxtA]);
	haveB = get(nxtB, b, nxtA);
	if (haveA > haveB) {
		return 1;
	}
	if (par[b][nxtA] == nxtB) {
		return 0;
	}

	haveB = get(nxtB, b, par[a][nxtB]);
	haveA = get(par[b][nxtA], nxtA, nxtB);

	if (haveB > haveA) {
		return 0;
	} else if (par[a][nxtB] == par[b][nxtA]) {
		return 1;
	} else {
		return dp[nxtA][nxtB];
	}
}

void calc_dp() {
	for (int len = 3; len < n; len++) {
		for (auto [a, b] : q[len]) {
			dp[a][b] = get_dp(a, b);
			dp[b][a] = get_dp(b, a);
		}
	}
}

int get_ans(int a, int b, int len) {
	int nxtA = par[b][a], nxtB = par[a][b];
	int haveA, haveB;

	haveA = get(a, nxtA);
	haveB = get(b, a);
	
	if (haveA > haveB) return 1;
	if (len == 1) return 0;
	
	haveA = get(nxtA, a, b);
	haveB = get(b, nxtB);
	
	if (haveB > haveA) return 0;
	if (len == 2) return 1;
	return dp[a][b];
}

void make_ans() {
	ans = 0;
	for (int len = 1; len < n; len++) {
		for (auto [a, b] : q[len]) {
			ans += get_ans(a, b, len);
			ans += get_ans(b, a, len);
		}
	}
}

void dfs_tin(int v, int p) {
	Tin[v] = timer++;
	for (auto i : gr[v]) {
		if (i == p) continue;
 		dfs_tin(i, v);
 	}
}

void renum() {
	timer = 0;
	dfs_tin(0, 0);
	for (int i = 0; i < n; i++) {
		g[Tin[i]] = gr[i];
		for (auto &j : g[Tin[i]]) {
			j = Tin[j];
		}
	}
}

void run() {
	renum();
	build();
	calc_dp();
	make_ans();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}