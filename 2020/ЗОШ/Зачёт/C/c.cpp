#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int INF = 1e9 + 228;


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

struct Stack{
	vector<int> st;
	vector<int> Min;
	Stack() {}
	void push(int x) {
		st.push_back(x);
		Min.push_back(x);
		if (Min.size() >= 2) {
			Min[Min.size() - 1] = min(Min.back(), Min[Min.size() - 2]);
		}
	}
	void pop() {
		assert(!st.empty());
		st.pop_back();
		Min.pop_back();
	}
	int get_val() {
		assert(!st.empty());
		return st.back();
	}
	int get_ans() {
		if (Min.empty()) return INF;
		return Min.back();
	}
};

struct Queue{
	Stack front, back;
	Queue() {
		front = {};
		back = {};
	}
	void push(int x) {
		back.push(x);
	}
	void pop() {
		if (front.st.empty()) {
			while (!back.st.empty()) {
				front.push(back.get_val());
				back.pop();
			}
		}
		front.pop();
	}
	int get_ans() {
		assert(!front.st.empty() || !back.st.empty());
		return min(front.get_ans(), back.get_ans());
	}
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, k;
	vector<int> a;
	n = readInt();
	k = readInt();
	k = min(2 * n + k % 2, k);
	a.resize(n);
	for (auto &i : a)
		i = readInt();
	vector<int> ans(n, INF);

	Queue q;
	for (int i = -k; i <= k; i += 2) {
		int pos = (i % n + n) % n;
		q.push(a[pos]);
	}

	for (int i = 0; i < n; i += 2) {
		ans[i] = q.get_ans();
		q.pop();
		int pos = (i + k + 2) % n;
		q.push(a[pos]);
	}

	q = Queue();


	for (int i = -k + 1; i <= k + 1; i += 2) {
		int pos = (i % n + n) % n;
		q.push(a[pos]);
	}

	for (int i = 1; i < n; i += 2) {
		ans[i] = q.get_ans();
		q.pop();
		int pos = (i + k + 2) % n;
		q.push(a[pos]);
	}

	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}











