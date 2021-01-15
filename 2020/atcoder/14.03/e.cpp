#pragma GCC optmize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

string a, b, c;

void read() {
	cin >> a >> b >> c;
}

bool check(char a, char b) {
	if (a == '$' || b == '$') return false;
	if (a == '?' || b == '?' || a == b) return true;
	return false;
}

const int MAXN = 6010;
int z[MAXN];

void z_function(string & s) {
	int n = s.size();
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		z[i] = 0;
		if (r >= i) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (i + z[i] < n && check(s[z[i]], s[z[i] + i])) z[i]++;
		if (i + z[i] - 1 > r) {
			l = i, r = i + z[i] - 1;
		}
	}
}

bool check(string & a, string & b) {
	string s = a + "$" + b;
	z_function(s);
	for (int i = a.size() + 1; i < s.size(); i++) {
		if (z[i] == a.size()) {
			return true;
		}
	}
	return false;
}

int solve(string & a, string & b){
	string s = b + "$" + a;
	if (check(a, b)) return 0;
	if (check(b, a)) return 0;
	z_function(s);
	for (int i = (int)s.size() - 1; i >= b.size() + 1; i--) {
		if (z[i] == s.size() - i) {
			return b.size() - (s.size() - i);
		}
	}
	return b.size();
}

bool check(string & a, int la, int ra, string & b, int lb) {
	if (la > ra) return true;
	for (int i = 0; i <= ra - la; i++) {
		if (!check(a[la + i], b[lb + i])) {
			return false;
		}
	}
	return true;
}

int solve(string & a, string & b, string & c) {
	int ans = a.size() + b.size() + c.size();
	string have = a + b;

	for (int len = 0; len <= min((int)a.size(), (int)b.size()); len++) {
		if (check(a, a.size() - len, a.size() - 1, b, 0)) {
			chkmin(ans, (int)a.size() + (int)b.size() - len + solve(have, c));	
		}
		if (have.size() > a.size())
			have.erase(have.begin() + a.size());
	}
	return ans;
}

int ans;

void run() {
	ans = a.size() + b.size() + c.size();
	vector<string> have = {a, b, c};
	sort(all(have));
	do {
		chkmin(ans, solve(have[0], have[1], have[2]));
	} while (next_permutation(all(have)));
}

void write() {
	cout << ans << endl;
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