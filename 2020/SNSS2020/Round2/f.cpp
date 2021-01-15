#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 200 * 1024 * 1024
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
	 
	inline void readWord(string & s) { 
		int c = readChar();
		while (c > 32)
			s += c, c = getChar();
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

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) {
        if (c + 1 < val_range) ++l[c + 1];
        ++r[c];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA)
        if (i >= 1 && sl[i - 1]) {
            SA[l[vec[i - 1]]++] = i - 1;
        }
    fill(r.begin(), r.end(), 0);
    for (int c : vec)
        ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
        if (i >= 1 && !sl[i - 1]) {
            SA[--r[vec[i - 1]]] = i - 1;
        }
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
    const int n = vec.size();
    vector<int> SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i)
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
            new_lms_idx[k++] = SA[i];
        }
    int cur = 0;
    SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) {
            SA[j] = ++cur;
            continue;
        }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) {
                flag = true;
                break;
            }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i)
        lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) {
            new_lms_idx[i] = lms_idx[lms_SA[i]];
        }
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}

vector<int> buildSuffixArray(const vector<int> &s, const int LIM = 101000) {
   // cout << "puhh" << endl;
    auto ret = SA_IS(s, LIM);
    /*cout << "ret = " << endl;
    for (auto i : ret) {
    	cout << i << " ";
    }
    cout << endl;*/
    return ret;
}


vector<int> buildLCP(vector<int> & s, vector<int> & a) {
	int n = s.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++) {
		ra[a[i]] = i;
	}
	vector<int> lcp(n - 1);
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur--;
		chkmax(cur, 0);
		if (ra[i] == n - 1) {
			cur = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (s[i + cur] == s[j + cur]) cur++;
		lcp[ra[i]] = cur;
	}
	return lcp;
}

const int N = 2e6 + 1e5 + 1e5 + 228;
const int LOG = 22;

namespace sparseLCP{
	int n;
	int lg[N];
	int sparse[N][LOG];
	int merge(int a, int b) {
		return min(a, b);
	}
	void init(const vector<int> & a) {
		n = a.size();
		for (int i = 2; i < n; i++) {
			lg[i] = lg[i / 2] + 1;
		}
		for (int i = 0; i < n; i++) {
			sparse[i][0] = a[i];
		}
		for (int l = 1; l < LOG; l++) {
			for (int i = 0; i + (1 << l) <= n; i++) {
				sparse[i][l] = merge(sparse[i][l - 1], sparse[i + (1 << (l - 1))][l - 1]);
			}
		}
	}
	int get(int l, int r) {
		if (l > r) return 0;
		int log = lg[r - l];
		return merge(sparse[l][log], sparse[r - (1 << log) + 1][log]);
	}
};

int getLCP(int pos1, int pos2) {
	if (pos1 > pos2) swap(pos1, pos2);
	return sparseLCP::get(pos1, pos2 - 1);
}

int getAns(vector<int> & v, int x, int len) {
	int posR = lower_bound(all(v), x) - v.begin();
	int l = posR - 1, r = v.size();
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (getLCP(v[mid], x) >= len) {
			l = mid;
		} else {
			r = mid;
		}
	}
	int R = r;
	l = -1, r = posR;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (getLCP(v[mid], x) >= len) {
			r = mid;
		} else {
			l = mid;
		}
	}
	int L = l;
	return R - L - 1;
}

const int Q = 1e5 + 10;

namespace tree{
	int n;
	vector<int> tree[Q * 4];

	void build(int v, int tl, int tr, const vector<int> & a) {
		if (tl >= tr) return;
		if (tl == tr - 1) {
			tree[v] = {a[tl]};
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v].resize(tree[v * 2].size() + tree[v * 2 + 1].size());
		merge(all(tree[v * 2]), all(tree[v * 2 + 1]), tree[v].begin());
	}
	void init(const vector<int> & a) {
		n = a.size();
		build(1, 0, n, a);
	}
	int get(int v, int tl, int tr, int l, int r, int x, int len) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return getAns(tree[v], x, len);
		int tm = (tl + tr) / 2;
		return get(v * 2, tl, tm, l, r, x, len) + get(v * 2 + 1, tm, tr, l, r, x, len);
	}
	int get(int l, int r, int x, int len) {
		return get(1, 0, n, l, r + 1, x, len);
	}
};

string s;
int n, q;
int l[Q], r[Q];
string have[Q];

void read() {
	//cin >> s;
	readWord(s);
	n = s.size();
	//cin >> q;
	q = readInt();
	for (int i = 1; i <= q; i++) {
		//cin >> l[i] >> r[i] >> have[i];
		l[i] = readInt();
		r[i] = readInt();
		readWord(have[i]);
	}
}


int pos[Q];

void build() {
	vector<int> a;
	pos[0] = 0;
	for (auto i : s) {
		a.push_back(i + Q);
	}
	for (int i = 1; i <= q; i++) {
		a.push_back(-i + Q);
		pos[i] = a.size();
		for (auto x : have[i]) {
			a.push_back(x + Q);
		}
	}
	a.push_back(-q - 1 + Q);
	vector<int> suffixArray = buildSuffixArray(a);
	vector<int> lcp = buildLCP(a, suffixArray);
	sparseLCP::init(lcp);
	vector<int> rSuffixArray(suffixArray.size());
	for (int i = 0; i < suffixArray.size(); i++) {
		rSuffixArray[suffixArray[i]] = i;
	}
	for (int i = 1; i <= q; i++) {
		pos[i] = rSuffixArray[pos[i]];
	}
	vector<int> now(n);
	for (int i = 0; i < n; i++) {
		now[i] = rSuffixArray[i];
	}
	tree::init(now);
}

int get(int l, int r, int pos, int len) {
	r = r - len + 1;
	return tree::get(l, r, pos, len);
}

void run() {
	build();
	for (int i = 1; i <= q; i++) {
		writeInt(get(l[i], r[i], pos[i], have[i].size()), '\n');
	}
}

void write() {
	
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}