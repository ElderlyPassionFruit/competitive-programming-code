#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


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


const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, ROOT;
int a[MAXN];

void read() {
	//cin >> n >> ROOT;
	n = readInt();
	ROOT = readInt();
	ROOT--;
	for (int i = 0; i < n; i++) {
		//cin >> a[i];
		a[i] = readInt();
	} 
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		//cin >> u >> v;
		u = readInt();
		v = readInt();
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

const int INF = 1e9 + 228;

struct node{
	int val;
	int l, r;
	node() {
		val = INF;
	}
	node(int _l, int _r) {
		l = _l, r = _r;
		val = INF;
	}
};

const int MAXMEM = 5e6 + 10;
node tree[MAXMEM];
int topQ = 0;

int clone(int root) {
	tree[topQ] = node();
	tree[topQ].val = tree[root].val;
	tree[topQ].l = tree[root].l;
	tree[topQ].r = tree[root].r;
	topQ++;
	return topQ - 1;
}

int build(int tl, int tr) {
	if (tl == tr - 1) {
		tree[topQ++] = node(-1, -1);
		return topQ - 1;
	}
	int tm = (tl + tr) / 2;
	int l = build(tl, tm);
	int r = build(tm, tr);
	tree[topQ++] = node(l, r);
	return topQ - 1;
}

int get(int root, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return INF;
	assert(root != -1);
	//if (root == -1) return INF;
	if (tl >= l && tr <= r) {
		return tree[root].val;
	}
	int tm = (tl + tr) / 2;
	return min(get(tree[root].l, tl, tm, l, r), get(tree[root].r, tm, tr, l, r));
}

int upd(int root, int tl, int tr, int pos, int val) {
	if (tl >= pos + 1 || tr <= pos) return root;
	if (tl == tr - 1) {
		root = clone(root);
		chkmin(tree[root].val, val);
		return root;
	}
	root = clone(root);
	int tm = (tl + tr) / 2;
	tree[root].l = upd(tree[root].l, tl, tm, pos, val);
	tree[root].r = upd(tree[root].r, tm, tr, pos, val);
	tree[root].val = min(tree[tree[root].l].val, tree[tree[root].r].val);
	return root;
}

int upd(int root, int pos, int val) {
	return upd(root, 0, n, pos, val);
}

int roots[MAXN];
int base;
int h[MAXN];
int sz[MAXN];
int mx_h[MAXN];

void dfs_precalc(int v, int p, int len) {
	h[v] = len++;
	mx_h[v] = h[v];
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_precalc(i, v, len);
		sz[v] += sz[i];
		chkmax(mx_h[v], mx_h[i]);
	}
}
 
void relax(vector<pair<int, int>> & have, int pos, int val) {
	pos = have[0].first - pos;
	if (pos == have.size()) {
		have.push_back({have.back().first - 1, INF});
	} 
	chkmin(have[pos].second, val);
}
 
vector<pair<int,int>> dfs_build(int v) {
	if (g[v].empty()) {
		roots[v] = clone(base);
		roots[v] = upd(roots[v], h[v], a[v]);
		return {{h[v], a[v]}};
	}
	auto have = dfs_build(g[v][0]);
	roots[v] = clone(roots[g[v][0]]);
	roots[v] = upd(roots[v], h[v], a[v]);
	relax(have, h[v], a[v]);
	g[v].erase(g[v].begin());
	for (auto i : g[v]) {
		auto a = dfs_build(i);
		reverse(all(a));
		for (auto i : a) {
			relax(have, i.first, i.second);
			roots[v] = upd(roots[v], i.first, i.second);
		}
	}
	return have;
}

void build() {
	dfs_precalc(ROOT, ROOT, 0);
	for (int i = 0; i < n; i++) {
		if (g[i].empty()) continue;
		sort(all(g[i]), [&] (int a, int b) {return sz[a] > sz[b];});
		if (sz[g[i][0]] > sz[i]) {
			g[i].erase(g[i].begin());
		}
		sort(all(g[i]), [&] (int a, int b) {return mx_h[a] > mx_h[b];});
	}
	base = build(0, n);
	dfs_build(ROOT);
}

int get(int v, int l, int r) {
	return get(roots[v], 0, n, l, r + 1);
}

int last;

void solve(int v, int len) {
	last = get(v, h[v], min(n - 1, h[v] + len));
	//cout << last << "\n";
	writeInt(last, '\n');
	last %= n;
}

void run() {
	build();
	int q;
	//cin >> q;
	q = readInt();
	last = 0;
	while (q--) {
		int a, b;
		//cin >> a >> b;
		a = readInt();
		b = readInt();
		a += last;
		if (a >= n) a -= n;
		b += last;
		if (b >= n) b -= n;
		solve(a, b);
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//test();
	//exit(0);
	read();
	run();
	write();
	return 0;
}