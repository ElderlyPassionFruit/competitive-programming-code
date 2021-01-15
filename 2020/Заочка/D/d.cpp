#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 50*1024*1024
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

//mt19937 rnd(time(0));

const int MAXN = 1e6 + 10, MAXLOG = 21;

struct edge{
	int u, v;
	edge() {}
	edge(int a, int b) {
		u = a, v = b;
	}
};

bool operator<(const edge & a, const edge & b) {
	return tie(a.u, a.v) < tie(b.u, b.v);
}

int n, k;
int L[2][MAXN], R[2][MAXN];
edge g[2][MAXN * 2];
int topQ = 0;
int pos_s[2][MAXN];

int h[MAXN], dist[MAXN][MAXLOG], par[MAXN];

bool used[MAXN];
int sz[MAXN];
int centr;

int ans;
int l[MAXN], r[MAXN];

int near[MAXN];
int tin[MAXN], timer = 0;

inline void read() {
	n = readInt();
	k = readInt();
	
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n * k; j += n) {
			L[0][j] = readInt();
		}
		for (int j = i; j < n * k; j += n) {
			R[0][j] = readInt();
		}
	}
	int u, v;
	for (int i = 1; i < n; i++) {
		u = readInt();
		v = readInt();
		u--;
		v--;
		g[0][topQ++] = {u, v};
		g[0][topQ++] = {v, u};
	}
	sort(g[0], g[0] + topQ);
	for (int i = topQ - 1; i >= 0; i--) {
		pos_s[0][g[0][i].u] = i; 
	}
}

inline void dfs_centr(int v, int p, int size, int Len, int H){
	sz[v] = 1;
	int mx = 0;
	if (H != -1) dist[v][H] = Len++;
	for (int i = pos_s[1][v]; i < topQ && g[1][i].u == v; i++) {
		if (g[1][i].v != p && !used[g[1][i].v]) {
			dfs_centr(g[1][i].v, v, size, Len, H);
			sz[v] += sz[g[1][i].v];
			chkmax(mx, sz[g[1][i].v]);
		}
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

inline void find_centr(int v, int p, int size, int H) {
	assert(H < 21);
	par[v] = p;
	used[v] = true;
	h[v] = H;
	for (int i = pos_s[1][v]; i < topQ && g[1][i].u == v; i++) {
		if (!used[g[1][i].v]) {
			int fsz = sz[g[1][i].v];
			if (fsz > sz[v])
				fsz = size - sz[v];
			dfs_centr(g[1][i].v, v, fsz, 1, H);
			find_centr(centr, v, fsz, H + 1);
		}
	}
} 

inline void build() {
	dfs_centr(0, -1, n, 1, -1);
	find_centr(centr, -1, n, 0);
	for (int i = 0; i < n; i++)
		l[i] = i, r[i] = i;
}

inline void clear() {
	for (int i = 0; i < n; i++)
		near[i] = MAXN;
}

inline void add(int v) {
	int u = v;
	near[u] = 0;
	u = par[u];
	while (u != -1) {
		chkmin(near[u], dist[v][h[u]]);
		u = par[u];
	}
}

inline void relax(int v) {
	int u = v;
	chkmin(ans, near[u]);
	u = par[u];
	while (u != -1) {
		chkmin(ans, dist[v][h[u]] + near[u]);	
		u = par[u];
	}
}

inline void solve(int pos) {
	clear();
	pos *= n;
	sort(l, l + n, [&] (int a, int b) {return L[1][pos + a] < L[1][pos + b];});
	sort(r, r + n, [&] (int a, int b) {return R[1][pos + a] < R[1][pos + b];});
	int p = 0;
	for (int i = 0; i < n; i++) {
		while (p < n && R[1][pos + r[p]] < L[1][pos + l[i]]) {
			add(r[p]);
			p++;
		}
		relax(l[i]);
	}
}

inline void dfs(int v, int p) {
	tin[v] = timer++;
	for (int i = pos_s[0][v]; i < topQ && g[0][i].u == v; i++) {
		if (g[0][i].v != p) {
			dfs(g[0][i].v, v);
		}
	}
}

inline void renum() {
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n * k; j += n) {
			L[1][j + tin[i]] = L[0][j + i];
			R[1][j + tin[i]] = R[0][j + i];
		}
	}
	for (int i = 0; i < n; i++) {
		pos_s[1][tin[i]] = pos_s[0][i];
	}
	for (int i = 0; i < topQ; i++) {
		g[1][i] = {tin[g[0][i].u], tin[g[0][i].v]};
	}
}

inline void run() {
	ans = n + 1;
	renum();
	build();
	for (int i = 0; i < k; i++)
		solve(i);
	if (ans == n + 1)
		ans = -1;
}

inline void write() {
	cout << ans;
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