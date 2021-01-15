#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 30 * 1024 * 1024
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

namespace solver1{
	#define int ll
	struct pref_array{
		vector<int> a;
		vector<int> pref;
		vector<int> suff;
		int n;
		pref_array(vector<int> _a) {
			n = _a.size();
			if (n == 0) return;
			a = _a;
			sort(all(a));
			pref.resize(n);
			pref[0] = 0;
			for (int i = 1; i < n; i++) {
				pref[i] += pref[i - 1];
				pref[i] += (a[i] - a[i - 1]) * i;
			} 
			suff.resize(n);
			suff[n - 1] = 0;
			for (int i = n - 2; i >= 0; i--) {
				suff[i] += suff[i + 1];
				suff[i] += (a[i + 1] - a[i]) * (n - 1 - i);
			}
		} 

		int get(int pos) {
			return pref[pos] + suff[pos];
		}

		int solve() {
			if (a.empty()) return 0;
			int ans = 1e15;
			for (int i = 0; i < n; i++) {
				chkmin(ans, get(i));
			}
			return ans;
		}
	};

	int n;
	vector<int> a;
	ll ans;
	void read() {
		//cin >> n;
		n = readInt();
		for (int i = 0; i < n; i++) {
			char x, y;
			int va, vb;
			//cin >> x >> va >> y >> vb;
			x = readChar();
			va = readInt();
			y = readChar();
			vb = readInt();
			if (x == y) {
				ans += abs(va - vb);
				continue;
			}
			ans++;
			a.push_back(va);
			a.push_back(vb);
		}
	}

	
	void run() {
		pref_array have(a);
		ans += have.solve();
	}

	void write() {
		cout << ans << endl;
	}
}

namespace solver2{
	struct optimum{
		priority_queue<int> L, R;
		ll sumL, sumR;
		optimum() {
			L = {};
			R = {};
			sumL = sumR = 0;
		}

		void relax() {
			while ((int)L.size() > (int)R.size()) {
				int x = L.top();
				L.pop();
				sumL -= x;
				sumR += x;
				R.push(-x);
			}
			while ((int)L.size() + 1 < (int)R.size()) {
				int x = -R.top();
				R.pop();
				sumR -= x;
				sumL += x;
				L.push(x);
			}
			while (!L.empty() && !R.empty() && L.top() > -R.top()) {
				int x = L.top();
				int y = -R.top();
				sumL -= x;
				sumL += y;
				sumR -= y;
				sumR += x;
				L.pop();
				R.pop();
				L.push(y);
				R.push(-x);
			}
		}

		void add(int a) {
			L.push(a);
			sumL += a;
			relax();
		} 

		ll get() {
			if (L.empty()) return 0;
			int mid = L.top();
			return (ll)L.size() * mid - sumL + sumR - (ll)R.size() * mid;
		}
	};

	int n;
	vector<pair<int, int>> a;
	ll ans;
	void read() {
		n = readInt();
		for (int i = 0; i < n; i++) {
			char x, y;
			int va, vb;
			x = readChar();
			va = readInt();
			y = readChar();
			vb = readInt();
			if (x == y) {
				ans += abs(va - vb);
				continue;
			}
			ans++;
			a.push_back({min(va, vb), max(va, vb)});
		}
	}

	void run() {  
		ll fans = 1e18;	
		if (a.empty()) fans = 0;
		
		sort(all(a), [&] (pair<int, int> i, pair<int, int> j) {return i.first + i.second < j.first + j.second;});
		vector<ll> add(a.size());
		optimum L;
		for (int i = 0; i < (int)a.size(); i++) {
			L.add(a[i].first);
			L.add(a[i].second);
			add[i] += L.get();
		}
		chkmin(fans, L.get());
		L = optimum();
		for (int i = (int)a.size() - 1; i > 0; i--) {
			L.add(a[i].first);
			L.add(a[i].second);
			add[i - 1] += L.get();
		}
		for (auto i : add)
			chkmin(fans, i);
		ans += fans;
	}

	void write() {
		cout << ans << endl; 
	}
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	t = readInt();
	if (t == 1) {
		solver1::read();
		solver1::run();
		solver1::write();
	} else {
		solver2::read();
		solver2::run();
		solver2::write();
	}
	return 0;  
}    
    


   
