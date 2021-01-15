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

#define FAST_ALLOCATOR_MEMORY 50*1024*1024
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


const int MAXN = 2010;
int a[MAXN][MAXN];
int n, m;
pair<int, int> pos_min;
void read() {
	cin >> n >> m;
	pos_min = {0, 0};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			if (a[i][j] < a[pos_min.first][pos_min.second])
				pos_min = {i, j};
		}
	}
}

vector<int> table_left[MAXN], table_right[2][MAXN];

void build() {
	for (int i = 0; i < n; i++) {
		vector<int> have(m);
		for (int j = 0; j < m; j++)
			have[j] = a[i][j];
		table_left[i] = table_right[0][i] = table_right[1][i] = have;
		
		for (int j = 1; j < m; j++)
			chkmax(table_left[i][j], table_left[i][j - 1]);

		for (int j = m - 2; j >= 0; j--)
			chkmin(table_right[0][i][j], table_right[0][i][j + 1]);
		
		for (int j = m - 2; j >= 0; j--)
			chkmax(table_right[1][i][j], table_right[1][i][j + 1]);
	}
}

const int INF = 1e9 + 10;

bool check(int mid, vector<int> & len) {
	int Min = INF, Max = -INF;
	for (int i = 0; i < n; i++) {
		if (len[i] == m - 1) continue;
		chkmin(Min, table_right[0][i][len[i] + 1]);
		chkmax(Max, table_right[1][i][len[i] + 1]);
	}
	return Max - Min <= mid;
}

bool check(int mid) {
	int x = a[pos_min.first][pos_min.second] + mid;
	vector<int> len;
	for (int i = 0; i < n; i++) {
		int pos;
		pos = --upper_bound(all(table_left[i]), x) - table_left[i].begin();
		len.push_back(pos);
	}

	vector<int> have;
	have = len;
	for (int i = 1; i < n; i++) {
		chkmin(have[i], have[i - 1]);
	}
	if (check(mid, have)) return true;
	have = len;
	for (int i = n - 2; i >= 0; i--) {
		chkmin(have[i], have[i + 1]);
	}
	if (check(mid, have)) return true;
	return false;
}

int calc() {
	build();
	int l = -1, r = INF;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	return r;
}

void rebuild() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1 - j; j++) {
			swap(a[i][j], a[i][m - 1 - j]);
		}
	}
	pos_min.second = m - 1 - pos_min.second;
}

int ans;

void run() {
	ans = INF;
	chkmin(ans, calc());
	rebuild();
	chkmin(ans, calc());
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