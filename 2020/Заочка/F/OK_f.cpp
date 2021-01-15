#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 200*1024*1024
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

namespace Queue{
	set<int> a;
	void add(int x) {
		a.insert(x);
	}
	void del(int x) {
		a.erase(x);
	}
	int get_min(int pos) {
		auto it = a.upper_bound(pos);
		if (a.empty() || it == a.end()) return -1;
		return *it;
	}
	int get_max(int pos) {
		auto it = a.upper_bound(pos);
		if (a.empty() || it == a.begin()) return -1;
		--it;
		return *it;
	}
};

struct query{
	int pos, ind;
	query() {}
	query(int a, int b) {
		pos = a, ind = b;
	}
};

const int MAXN = 1e6 + 10;

int n, q, k;
int a[MAXN];

vector<query> lq[MAXN];
vector<int> add[MAXN];
int l[MAXN][2];
int ans[MAXN];
int pos_l[MAXN];
int pos_r[MAXN];

void read() {
	n = readInt();
	q = readInt();
	k = readInt();
	for (int i = 0; i < n; i++)
		a[i] = readInt();
	for (int i = 0; i < q; i++) {
		int l, r;
		l = readInt();
		r = readInt();
		l--;
		r--;
		lq[l].push_back({r, i});
	}
}

struct event{
	int val, pos;
	event() {}
	event(int a, int b) {
		val = a, pos = b;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.val, a.pos) < tie(b.val, b.pos);
}

void build() {
	vector<event> have(n);
	for (int i = 0; i < n; i++) {
		have[i].val = a[i];
		have[i].pos = i;
	}
	sort(all(have));
	int pos = 0;
	for (int i = 0; i < n; i++) {
		while (pos < i && have[pos].val + k < have[i].val) {
			Queue::del(have[pos].pos);
			pos++;
		} 
		l[have[i].pos][0] = Queue::get_max(have[i].pos);
		l[have[i].pos][1] = Queue::get_min(have[i].pos);
		Queue::add(have[i].pos);
	}
}

namespace fenvik{
	int n;
	int tree[MAXN];
	
	void init(int sz) {
		n = sz;
		for (int i = 0; i < n; i++)
			tree[i] = 0;
	}
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos |= (pos + 1))
			tree[pos] += val;
	}
};

void solve() {
	fenvik::init(n);
	for (int i = n - 1; i >= 0; i--) {
		if (l[i][0] != -1)
			add[l[i][0]].push_back(i);
		if (l[i][1] != -1)
			fenvik::upd(l[i][1], 1);
		for (auto j : add[i]) {
			fenvik::upd(j, 1);
			if (l[j][1] != -1)
				fenvik::upd(l[j][1], -1);
		}
		for (auto j : lq[i])
			ans[j.ind] += fenvik::get(i, j.pos);
	}
	for (int i = 0; i < n; i++) {
		for (auto j : lq[i]) {
			ans[j.ind] = j.pos - i + 1 - ans[j.ind];
		}
	}
}

void run() {
	build();
	solve();
}

void write() {
	for (int i = 0; i < q; i++)
		cout << ans[i] << ' ';
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