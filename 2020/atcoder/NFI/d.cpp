#pragma GCC target("sse,sse2,sse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

const int MAXLOG = 18;
const int MAXN = ((1 << MAXLOG) + 228) * 10;
const int BUBEN = 11;
int n;
int v[MAXN], w[MAXN];

void read() {
	n = readInt();
	for (int i = 1; i <= n; ++i) {
		v[i] = readInt();
		w[i] = readInt();
	}
}

int getHeight(int v) {
	int ans = 0;
	while (v) {
		ans++;
		v /= 2;
	}
	return ans;
}

pair<int, int> fans[MAXN];
int topFans[MAXN];
int start[MAXN];
int revOrder[MAXN];

int have[MAXLOG];
int topHave;

void build(int v) {
	topHave = 0;
	while (v) {
		have[topHave++] = v;
		v /= 2;
	}
	reverse(have, have + topHave);
} 

void precalc() {
	int pos = 0;
	for (int V = 0; V < n; ++V) {
		if (getHeight(V) != BUBEN) continue;
		revOrder[V] = pos;
		build(V);
		topFans[pos] = 0;
		if (pos > 0) start[pos] = start[pos - 1] + topFans[pos - 1];
		for (int mask = 0; mask < (1 << topHave); ++mask) {
			int sum = 0;
			int now = 0;
			for (int bit = 0; bit < topHave; ++bit) {
				if ((mask >> bit) & 1) {
					sum += w[have[bit]];
					now += v[have[bit]];
				}
			}
			fans[start[pos] + topFans[pos]++] = {sum, now};
		}
		sort(fans + start[pos], fans + start[pos] + topFans[pos]);
		for (int i = 1; i < topFans[pos]; ++i) {
			chkmax(fans[start[pos] + i].second, fans[start[pos] + i - 1].second);
		}
		++pos;
	}
}

void stupid(int l) {
	int ans = 0;
	for (int mask = 0; mask < (1 << topHave); mask++) {
		int sum = 0;
		int now = 0;
		for (int bit = 0; bit < topHave; bit++) {
			if ((mask >> bit) & 1) {
				sum += w[have[bit]];
				now += v[have[bit]];
			}
			if (sum > l) break;
		}
		if (sum <= l) {
			chkmax(ans, now);
		} 
	}
	writeInt(ans, '\n');
}

void smart(int l) {	
	int szL = BUBEN;
	int szR = topHave - szL;
	int pos = revOrder[have[BUBEN - 1]];
	int ans = 0;
	for (int mask = 0; mask < (1 << szR); ++mask) {
		int sum = 0;
		int now = 0;
		for (int bit = 0; bit < szR; ++bit) {
			if ((mask >> bit) & 1) {
				sum += w[have[bit + szL]];
				now += v[have[bit + szL]];
			}
			if (sum > l) break;
		}
		if (sum > l) continue;
		chkmax(ans, now);
		int mypos = lower_bound(fans + start[pos], fans + start[pos] + topFans[pos], make_pair(l - sum + 1, 0)) - fans - start[pos];
		mypos--;
		if (mypos >= 0 && mypos < topFans[pos]) {
			chkmax(ans, now + fans[start[pos] + mypos].second);
		}
	}
	writeInt(ans, '\n');
}

void solve() {
	int v, l;
	v = readInt();
	l = readInt();
	build(v);
	if (topHave <= BUBEN) {
		stupid(l);
	} else {
		smart(l);
	}
}

void run() {
	precalc();
	int q;
	q = readInt();
	while (q--) {
		solve();
	}
}

signed main() {
	read();
	run();
	return 0;
}