//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,avx,avx2")
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

const int MAXN = 5e5 + 10;
const int MAXMEM = 15e6 + 10;
namespace presistent_segment_tree{
	struct node{
		int l, r;
		int val;
		node() {
			l = -1, r = -1, val = 0;
		}
	};

	node tree[MAXMEM];
	int topQ = 0;
	int n;
	int root;

	int clone(int root) {
		tree[topQ] = node();
		tree[topQ].l = tree[root].l;
		tree[topQ].r = tree[root].r;
		tree[topQ].val = tree[root].val;
		topQ++;
		return topQ - 1; 
	}

	int build(int tl, int tr) {
		if (tl == tr - 1) {
			tree[topQ] = node();
			topQ++;
			return topQ - 1;
		}
		int tm = (tl + tr) / 2;
		int l = build(tl, tm);
		int r = build(tm, tr);
		tree[topQ] = node();
		tree[topQ].l = l;
		tree[topQ].r = r;
		topQ++;
		return topQ - 1;
	}

	int upd(int root, int tl, int tr, int pos, int val) {
		if (tl >= pos + 1 || tr <= pos) return root;
		root = clone(root);
		if (tl == tr - 1) {
			tree[root].val += val;
			return root;
		}
		int tm = (tl + tr) / 2;
		tree[root].l = upd(tree[root].l, tl, tm, pos, val);
		tree[root].r = upd(tree[root].r, tm, tr, pos, val);
		tree[root].val = tree[tree[root].l].val + tree[tree[root].r].val;
		return root;
	}

	int upd(int root, int pos, int val) {
		return upd(root, 0, n, pos, val);
	}

	int roots[MAXN];

	void init(const vector<int> & a) {
		n = a.size();
		roots[0] = build(0, n);
		for (int i = 1; i <= n; i++) {
			roots[i] = upd(roots[i - 1], a[i - 1], 1);
		}
	}

	pair<int, int> get_kth(int rootL, int rootR, int tl, int tr, int k) {
		if (tree[rootR].val - tree[rootL].val < k) return {-1, -1};
		if (tl == tr - 1) return {tl, tree[rootR].val - tree[rootL].val};
		int tm = (tl + tr) / 2;
		pair<int, int> ans = get_kth(tree[rootL].l, tree[rootR].l, tl, tm, k);
		if (ans.first == -1) {
			ans = get_kth(tree[rootL].r, tree[rootR].r, tm, tr, k - (tree[tree[rootR].l].val - tree[tree[rootL].l].val));
		}
		return ans;
	}

	pair<int, int> get_kth(int l, int r, int k) {
		return get_kth(roots[l - 1], roots[r], 0, n, k);
	}
};

int n, q;
vector<int> a;

void read() {
	//cin >> n >> q;
	n = readInt();
	q = readInt();
	a.resize(n);
	for (auto &i : a) {
		//cin >> i;
		i = readInt();
		i--;
	}
}

void run() {
	presistent_segment_tree::init(a);
	while (q--) {
		int l, r;
		//cin >> l >> r;
		l = readInt();
		r = readInt();
		int x;
		x = (r - l + 2) / 2;
		pair<int, int> have = presistent_segment_tree::get_kth(l, r, x);
		if (have.second > (r - l + 1) / 2) {
			writeInt(have.first + 1, '\n');
			continue;
		}
		writeInt(0, '\n');
	}
}

void write() {

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