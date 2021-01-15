#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,avx,avx2,abm,mmx")
#pragma GCC optimize("O3,unroll-loops,inline")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


#define FAST_ALLOCATOR_MEMORY 100*1024*1024
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

const int MAXN = 810;
const int MAXM = 1e6 + 10;
namespace matroid_intersection{
	// Кто это читает тот ЗЗЗДОХНЕТ
	struct edge{
		int v, u;
		edge() {}
		edge(int a, int b) {
			v = a, u = b;
		}
	};

	struct Ed{
		int v, ind;
		Ed() {}
		Ed(int a, int b) {
			v = a, ind = b;
		}
	};

	const ll INF = 1e18;

	int n, m;
	bool S[MAXN], y[MAXN][2];

	int topG = 0, topQ = 0, topL, topR = 0; 
	edge g[MAXM], have[MAXN][2];
	int Q[MAXN], l[MAXN], r[MAXN];
	int W[MAXN], w[MAXN];
	ll ans = 0;
	vector<Ed> G[MAXN];
	int color[MAXN];

	ll dist[MAXN];
	int par[MAXN], len[MAXN];


	void bfs(int v, int c, int flag) {
		topQ = 0;
		Q[topQ] = v;
		
		topQ++;
		color[v] = c;
		while (topQ) {
			topQ--;
			v = Q[topQ];
			for (auto i : G[v]) {
				if (i.ind == flag) continue;
				if (color[i.v]) continue;
				color[i.v] = c;
				Q[topQ] = i.v;
				topQ++;
			}
		}
	}

	void make(int flag) {
		for (int i = 0; i < n; i++)
			color[i] = 0;
		int c = 1;
		for (int i = 0; i < n; i++) {
			if (!color[i]) {
				bfs(i, c++, flag);
			}
		}
	}

	bool build() {
		topG = 0;
		topL = 0, topR = 0;
		for (int i = 0; i < m; i++) {
			if (S[i])
				l[topL++] = i;
			else
				r[topR++] = i;
		}

		for (int it = 0; it < 2; it++) {
			for (int i = 0; i < n; i++)
				G[i].clear();

			for (int pos = 0; pos < topL; pos++) {
				int i = l[pos];
				G[have[i][it].v].push_back({have[i][it].u, i});
				G[have[i][it].u].push_back({have[i][it].v, i});
			}

			make(-1);
			bool f = false;
			for (int i = 0; i < m; i++) {
				y[i][it] = false;
				if (S[i]) continue;
				y[i][it] = color[have[i][it].v] != color[have[i][it].u];
				f |= y[i][it];
			}
			if (!f) return false;

			for (int posl = 0; posl < topL; posl++) {
				int i = l[posl];
				make(i);
				for (int posr = 0; posr < topR; posr++) {
					int j = r[posr];
					if (color[have[j][it].v] != color[have[j][it].u]){
						if (it == 0)
							g[topG++] = edge(i, j);
						else
							g[topG++] = edge(j, i);
					}
				}
			}
		}
		for (int i = 0; i < m; i++) 
			w[i] = (S[i] ? W[i] : -W[i]);
		return true;
	}

	bool stupid_solve() {
		int v = -1;
		for (int i = 0; i < m; i++) {
			if (y[i][0] && y[i][1]) {
				if (v == -1 || W[i] > W[v])
					v = i;
			}
		}
		if (v == -1)
			return false;
		
		S[v] = true;
		ans += W[v];
		return true;
	}

	bool smart_solve() {
		for (int i = 0; i < m; i++)
			par[i] = -1, dist[i] = INF, len[i] = m + 1;
		for (int i = 0; i < m; i++) {
			if (y[i][0]) {
				dist[i] = w[i];
				len[i] = 0;
			}
		}
		
		while (true) {
			bool flag = true;
			for (int i = 0; i < topG; i++) {
				int v = g[i].v;
				int u = g[i].u;
				if (dist[v] == INF) continue;
				ll nd = w[u] + dist[v];
				int nl = len[v] + 1;
				if (tie(dist[u], len[u]) <= tie(nd, nl)) continue;
				par[u] = v;
				dist[u] = nd;
				len[u] = nl;
				flag = false;
			}
			if (flag) break;
		}
	
		int v = -1;
		for (int i = 0; i < m; i++) {
			if (!y[i][1]) continue;
			if (dist[i] == INF) continue;
			if (v == -1) {
				v = i;
				continue;
			}
			if (tie(dist[v], len[v]) > tie(dist[i], len[i]))
				v = i;
		}

		if (v == -1) return false;
		while (par[v] != -1) {
			S[v] = S[v] ^ 1;
			if (S[v])
				ans += W[v];
			else
				ans -= W[v];
			v = par[v];
		}

		S[v] = S[v] ^ 1;
		if (S[v]) 
			ans += W[v]; 
		else
			ans -= W[v];
		return true;
	}

	bool agment(){
		if (!build()) return false;
		int cnt = 0;
		for (int i = 0; i < m; i++)
			cnt += S[i];
		if (cnt == 0) return stupid_solve();
		return smart_solve();
	};
};

using namespace matroid_intersection;

void read() {
	n = readInt();
	m = readInt();
	for (int i = 0; i < m; i++) {
		have[i][0].v = readInt();
		have[i][0].u = readInt();
		have[i][0].v--, have[i][0].u--;
		have[i][1].v = readInt();
		have[i][1].u = readInt();
		have[i][1].v--, have[i][1].u--;
		W[i] = readInt();
	} 
	vector<int> x(n);
	iota(all(x), 0);
	random_shuffle(all(x));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 2; j++) {
			have[i][j].u = x[have[i][j].u];
			have[i][j].v = x[have[i][j].v];
		}
	}
}

vector<ll> out;

void run() {
	for (int i = 1; i <= m; i++) {
		bool flag = agment();
		if (flag)
			out.push_back(ans);
		else {
			while (out.size() < m)
				out.push_back(INF);
			break;
		}
	}
}

void write() {
	for (auto i : out) {
		if (i == INF) {
			cout << "Impossible" << '\n';
		} 
		else {
			cout << i << '\n';
		}
	}
}

signed main() {
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}