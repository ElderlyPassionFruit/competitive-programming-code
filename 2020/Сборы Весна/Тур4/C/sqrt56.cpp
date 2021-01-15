#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
//#pragma GCC optimize("inline")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const int BUBEN = 380;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 20 * 1024 * 1024
#ifdef FAST_ALLOCATOR_MEMORY
int ptr = 0;
char memory[(int) FAST_ALLOCATOR_MEMORY];
 
inline void *operator new(size_t n) {
	char *res = memory + ptr;
	ptr += n;
	return (void *)  res; 
}  
  
inline void operator delete(void *) noexcept {}
inline void operator delete(void *, size_t) {}
#endif

namespace fast {
	/** Fast input-output */
	 
	template <class T = int> inline T readInt();						
	inline double readDouble();
	inline int readUInt();					 
	inline int readChar(); // first non-blank character
	inline void readWord(char *s); 
	inline bool readLine(char *s); // do not save '\n'
	inline bool isEof();
	inline int getChar(); 
	inline int peekChar();
	inline bool seekEof();
	inline void skipBlanks();
	 
	template <class T> inline void writeInt(T x, char end = 0, int len = -1);
	inline void writeChar(int x); 
	inline void writeWord(const char *s);
	inline void writeDouble(double x, int len = 0);
	inline void flush();
	 
	static struct buffer_flusher_t {
		~buffer_flusher_t() {
			flush();
		}
	} buffer_flusher;
	 
	/** Read */
	 
	static const int buf_size = 4096;
	 
	static unsigned char buf[buf_size];
	static int buf_len = 0, buf_pos = 0;
	 
	inline bool isEof() {
		if (buf_pos == buf_len) {
			buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
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
	 
	inline bool seekEof() { 
		int c;
		while ((c = peekChar()) != -1 && c <= 32)
			buf_pos++;
		return c == -1;
	}
	 
	inline void skipBlanks() {
		while (!isEof() && buf[buf_pos] <= 32U)
			buf_pos++;
	}
	 
	inline int readChar() {
		int c = getChar();
		while (c != -1 && c <= 32)
			c = getChar();
		return c;
	}
	 
	inline int readUInt() {
		int c = readChar(), x = 0;
		while ('0' <= c && c <= '9')
			x = x * 10 + c - '0', c = getChar();
		return x;
	}
	 
	template <class T>
	inline T readInt() {
		int s = 1, c = readChar();
		T x = 0;
		if (c == '-')
			s = -1, c = getChar();
		else if (c == '+')
			c = getChar();
		while ('0' <= c && c <= '9')
			x = x * 10 + c - '0', c = getChar();
		return s == 1 ? x : -x;
	}
	 
	inline double readDouble() {
		int s = 1, c = readChar();
		double x = 0;
		if (c == '-')
			s = -1, c = getChar();
		while ('0' <= c && c <= '9')
			x = x * 10 + c - '0', c = getChar();
		if (c == '.') {
			c = getChar();
			double coef = 1;
			while ('0' <= c && c <= '9')
				x += (c - '0') * (coef *= 1e-1), c = getChar();
		}
		return s == 1 ? x : -x;
	}
	 
	inline void readWord(char *s) { 
		int c = readChar();
		while (c > 32)
			*s++ = c, c = getChar();
		*s = 0;
	}
	 
	inline bool readLine(char *s) { 
		int c = getChar();
		while (c != '\n' && c != -1)
			*s++ = c, c = getChar();
		*s = 0;
		return c != -1;
	}
	 
	/** Write */
	 
	static int write_buf_pos = 0;
	static char write_buf[buf_size];
	 
	inline void writeChar(int x) {
		if (write_buf_pos == buf_size)
			fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
		write_buf[write_buf_pos++] = x;
	}
	 
	inline void flush() {
		if (write_buf_pos) {
			fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
			fflush(stdout);
		}
	}
	 
	template <class T> 
	inline void writeInt(T x, char end, int output_len) {
		if (x < 0)
			writeChar('-'), x = -x;
	 
		char s[24];
		int n = 0;
		while (x || !n)
			s[n++] = '0' + x % 10, x /= 10;
		while (n < output_len)
			s[n++] = '0';
		while (n--)
			writeChar(s[n]);
		if (end)
			writeChar(end);
	}
	 
	inline void writeWord(const char *s) {
		while (*s)
			writeChar(*s++);
	}
	 
	inline void writeDouble(double x, int output_len) {
		if (x < 0)
			writeChar('-'), x = -x;
		int t = (int)x;
		writeInt(t), x -= t;
		writeChar('.');
		for (int i = output_len - 1; i > 0; i--) {
			x *= 10;
			t = std::min(9, (int)x);
			writeChar('0' + t), x -= t;
		}
		x *= 10;
		t = std::min(9, (int)(x + 0.5));
		writeChar('0' + t);
	}
}

using namespace fast;

struct pt{
	int x, y, ind;
	pt() {}
	pt(int _x, int _y, int _ind) {
		x = _x, y = _y, ind = _ind;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

const int MAXN = 1e5 + 10;
const int MAXLOG = 18;
int n;
pt a[MAXN];

void read() {
	//cin >> n;
	n = readInt();
	for (int i = 0; i < n; i++) {
		//cin >> a[i].x >> a[i].y;
		a[i].x = readInt();
		a[i].y = readInt();
		a[i].ind = i;
	}
	sort(a, a + n);
}

int lg[MAXN * 2];

namespace graph_x{
	vector<int> g[MAXN];
	int n;

	void add_edge(int v, int u) {
		g[v].push_back(u);
		g[u].push_back(v);
	}

	void init(int sz) {
		n = sz;
	}

	int tin[MAXN], h[MAXN];
	int order[MAXN * 2];
	int timer = 0;

	void dfs(int v, int p, int len) {
		tin[v] = timer++;
		h[v] = len++;
		order[tin[v]] = v;
		for (auto i : g[v]) {
			if (i == p) continue;
			dfs(i, v, len);
			order[timer++] = v;
		}
	}

	int sparce[MAXN * 2][MAXLOG];

	void build() {
		for (int i = 0; i < n; i++) {
			sort(all(g[i]));
			g[i].resize(unique(all(g[i])) - g[i].begin());
		}
		dfs(0, 0, 0);
		lg[0] = lg[1] = 0;
		for (int i = 2; i < timer; i++)
			lg[i] = lg[i / 2] + 1;
		for (int i = 0; i < timer; i++) {
			sparce[i][0] = order[i];
		}
		for (int l = 1; l < MAXLOG; l++) {
			for (int i = 0; i + (1 << l) <= timer; i++) {
				int v = sparce[i][l - 1];
				int u = sparce[i + (1 << (l - 1))][l - 1];
				if (h[v] < h[u]) {
					sparce[i][l] = v;
				} else {
					sparce[i][l] = u;
				}
			}
		}
	}

	int lca(int v, int u) {
		v = tin[v];
		u = tin[u];
		if (v > u) swap(v, u);
		int l = lg[u - v];
		int ans;
		v = sparce[v][l];
		u = sparce[u - (1 << l) + 1][l];
		if (h[v] < h[u]) {
			ans = v;
		} else {
			ans = u;
		}
		/*int ans = order[v];
		for (int i = v; i <= u; i++) {
			if (h[ans] > h[order[i]]) {
				ans = order[i];
			}
		}*/
		return ans;
	}

	int dist(int u, int v) {
		return h[v] + h[u] - 2 * h[lca(v, u)];
	}
}

namespace graph_y{
	vector<int> g[MAXN];
	int n;

	void add_edge(int v, int u) {
		g[v].push_back(u);
		g[u].push_back(v);
	}

	void init(int sz) {
		n = sz;
	}

	int tin[MAXN], h[MAXN];
	int order[MAXN * 2];
	int timer = 0;

	void dfs(int v, int p, int len) {
		tin[v] = timer++;
		h[v] = len++;
		order[tin[v]] = v;
		for (auto i : g[v]) {
			if (i == p) continue;
			dfs(i, v, len);
			order[timer++] = v;
		}
	}

	int sparce[MAXN * 2][MAXLOG];

	void build() {
		for (int i = 0; i < n; i++) {
			sort(all(g[i]));
			g[i].resize(unique(all(g[i])) - g[i].begin());
		}
		dfs(0, 0, 0);
		lg[0] = lg[1] = 0;
		for (int i = 2; i < timer; i++)
			lg[i] = lg[i / 2] + 1;
		for (int i = 0; i < timer; i++) {
			sparce[i][0] = order[i];
		}
		for (int l = 1; l < MAXLOG; l++) {
			for (int i = 0; i + (1 << l) <= timer; i++) {
				int v = sparce[i][l - 1];
				int u = sparce[i + (1 << (l - 1))][l - 1];
				if (h[v] < h[u]) {
					sparce[i][l] = v;
				} else {
					sparce[i][l] = u;
				}
			}
		}
	}

	int lca(int v, int u) {
		v = tin[v];
		u = tin[u];
		if (v > u) swap(v, u);
		int l = lg[u - v];
		int ans;
		v = sparce[v][l];
		u = sparce[u - (1 << l) + 1][l];
		if (h[v] < h[u]) {
			ans = v;
		} else {
			ans = u;
		}
		/*int ans = order[v];
		for (int i = v; i <= u; i++) {
			if (h[ans] > h[order[i]]) {
				ans = order[i];
			}
		}*/
		return ans;
	}

	int dist(int u, int v) {
		return h[v] + h[u] - 2 * h[lca(v, u)];
	}
}

int ind_x[MAXN], ind_y[MAXN];

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, 1, -1};
 
int par_x[MAXN], par_y[MAXN];

int get_par_x(int v) {
	if (v == par_x[v]) return v;
	return par_x[v] = get_par_x(par_x[v]);
}

void uni_x(int a, int b) {
	a = get_par_x(a);
	b = get_par_x(b);
	if (a == b) return;
	par_x[a] = b;
}

int get_par_y(int v) {
	if (v == par_y[v]) return v;
	return par_y[v] = get_par_y(par_y[v]);
}

void uni_y(int a, int b) {
	a = get_par_y(a);
	b = get_par_y(b);
	if (a == b) return;
	par_y[a] = b;
}

void build_coord() {
	for (int i = 0; i < n; i++) {
		par_x[i] = par_y[i] = i;
	}

	for (int i = 0; i < n; i++) {
		int nx, ny, pos;
		nx = a[i].x + 1;
		ny = a[i].y;
		pos = lower_bound(a, a + n, pt(nx, ny, 0)) - a;
		if (pos != n && a[pos].x == nx && a[pos].y == ny) {
			uni_x(a[i].ind, a[pos].ind);
		}
		nx = a[i].x;
		ny = a[i].y + 1;
		pos = lower_bound(a, a + n, pt(nx, ny, 0)) - a;
		if (pos != n && a[pos].x == nx && a[pos].y == ny) {
			uni_y(a[i].ind, a[pos].ind);
		}
	}

	vector<int> coord_x, coord_y;
	for (int i = 0; i < n; i++) {
		coord_x.push_back(get_par_x(i));
		coord_y.push_back(get_par_y(i));
	}
	sort(all(coord_x));
	coord_x.resize(unique(all(coord_x)) - coord_x.begin());
	sort(all(coord_y));
	coord_y.resize(unique(all(coord_y)) - coord_y.begin());
	for (int i = 0; i < n; i++) {
		ind_x[i] = lower_bound(all(coord_x), get_par_x(i)) - coord_x.begin();
		ind_y[i] = lower_bound(all(coord_y), get_par_y(i)) - coord_y.begin();
	}

	graph_x::init(coord_x.size());
	graph_y::init(coord_y.size());
	for (int i = 0; i < n; i++) {
		int nx, ny, pos;
		nx = a[i].x;
		ny = a[i].y + 1;
		pos = lower_bound(a, a + n, pt(nx, ny, 0)) - a;
		if (pos != n && a[pos].x == nx && a[pos].y == ny) {
			graph_x::add_edge(ind_x[a[i].ind], ind_x[a[pos].ind]);
		}
		nx = a[i].x + 1;
		ny = a[i].y;
		pos = lower_bound(a, a + n, pt(nx, ny, 0)) - a;
		if (pos != n && a[pos].x == nx && a[pos].y == ny) {
			graph_y::add_edge(ind_y[a[i].ind], ind_y[a[pos].ind]);
		}
	}

	graph_x::build();
	graph_y::build();
}

const int INF = 1e9 + 10;
int fans[MAXN];
int Q[BUBEN + 1];
int topQ = 0;
vector<int> g[MAXN];
 
void build() {
	for (int i = 0; i < n; i++) {
		fans[i] = INF;
	}
	for (int i = 0; i < n; i++) {
		for (int d = 0; d < 4; d++) {
			int nx = a[i].x + dx[d];
			int ny = a[i].y + dy[d];
			int pos = lower_bound(a, a + n, pt(nx, ny, 0)) - a;
			if (pos == n) continue;
			if (a[pos].x != nx || a[pos].y != ny) continue;
			g[a[i].ind].push_back(a[pos].ind);
		}
	}
	build_coord();
}

int q[MAXN];
int topq = 0;

void bfs() {
	for (int i = 0; i < topQ; i++) {
		fans[Q[i]] = 0;
		q[topq++] = Q[i];
	}
	topQ = 0;
	while (topq) {
		int v = q[--topq];
		for (auto i : g[v]) {
			if (fans[i] <= fans[v] + 1) continue;
			fans[i] = fans[v] + 1;
			q[topq++] = i;
		}
	}
}

void rebuild() {
	if (topQ >= BUBEN)
		bfs();
}

int calc(int ind) {
	int ans = fans[ind];
	for (int i = 0; i < topQ; i++) {
		chkmin(ans, graph_x::dist(ind_x[ind], ind_x[Q[i]]) + graph_y::dist(ind_y[ind], ind_y[Q[i]]));
	}
	if (ans == INF) ans = -1;
	return ans;
}

void run() {
	build();
	int q;
	//cin >> q;
	q = readInt();	
	while (q--) {
		int type;
		//cin >> type;
		type = readInt();
		pt x;
		//cin >> x.x >> x.y;
		x.x = readInt();
		x.y = readInt();
		int pos = lower_bound(a, a + n, pt(x.x, x.y, 0)) - a;
		if (type == 1) {
			Q[topQ++] = a[pos].ind;
			rebuild();
		} else {
			//cout << calc(a[pos].ind) << "\n";
			writeInt(calc(a[pos].ind), '\n');
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}