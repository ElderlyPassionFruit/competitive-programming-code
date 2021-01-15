#include <cstdio>
#include <vector>
using namespace std;
#define sz(a) ((int) (a).size())
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
const int N = 150;
const int L = (int) 1e5;
const int M = (int) 1e9 + 7;
const int Q = (int) 20022179;
int n, m, q, qcnt, qnext[Q], qstart[N][N], ans[N + 1][N + 1];
vector< pair<int, int> > qa[L], qb[L], qc[L];
unsigned char qi[Q], qj[Q];
bool a[N][N];
char c;

void add(int& a, int b) {
	if ((a += b) >= M) a -= M;
}

void solve(int x, int y) {
	for (int i = x; i < n; ++i)
		for (int j = y; j < m; ++j)
			ans[i][j] = 0;
	ans[x][y] = 1;
	for (int i = x; i < n; ++i)
		for (int j = y; j < m; ++j) {
			if (!a[i][j] || !ans[i][j]) continue;
			add(ans[i + 1][j], ans[i][j]);
			add(ans[i][j + 1], ans[i][j]);
		}
	for (int i = qstart[x][y]; i != -1; ) {
		int ians = ((qi[i] >= x) && (qj[i] >= y)) ? ans[qi[i]][qj[i]] : 0, inext = qnext[i];
		qnext[i] = ians, i = inext;
	}
}

void add(const pair<int, int>& p1, const pair<int, int>& p2, int q) {
	qi[q] = p2.fs, qj[q] = p2.sc, qnext[q] = qstart[p1.fs][p1.sc], qstart[p1.fs][p1.sc] = q;
}

void add_all(const vector< pair<int, int> >& a, const vector< pair<int, int> >& b) {
	for (int i = 0; i < sz(a); ++i)
		for (int j = 0; j < sz(b); ++j)
			add(a[i], b[j], qcnt++);
}

void read(vector< pair<int, int> >& data) {
	int k, x, y;
	scanf("%d", &k);
	for (int i = 0; i < k; ++i)
		scanf("%d%d", &x, &y), data.pb(mp(x - 1, y - 1));
}

int main() {
	//freopen("turtle.in", "r", stdin);
	//freopen("turtle.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf(" %c", &c), a[i][j] = (c == '.'), qstart[i][j] = -1;
	scanf("%d", &q);
	for (int iq = 0; iq < q; ++iq) {
		read(qa[iq]), read(qb[iq]), read(qc[iq]);
		add_all(qa[iq], qc[iq]), add_all(qa[iq], qb[iq]), add_all(qb[iq], qc[iq]);
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (a[i][j])
				solve(i, j);
	qcnt = 0;
	for (int iq = 0; iq < q; ++iq) {
		int res = 0, ac, ab, bc, sa = sz(qa[iq]), sb = sz(qb[iq]), sc = sz(qc[iq]);
		for (int i = 0; i < sa; ++i)
			for (int k = 0; k < sc; ++k) {
				if (!(ac = qnext[qcnt + i * sc + k])) continue;
				for (int j = 0; j < sb; ++j) {
					ab = qnext[qcnt + sa * sc + i * sb + j];
					bc = qnext[qcnt + sa * sc + sa * sb + j * sc + k];
					res += (int) ((ac - ab * (long long) bc) % M != 0);
				}
			}
		printf("%d\n", res);
		qcnt += sa * sc + sa * sb + sb * sc;
	}
	return 0;
}
