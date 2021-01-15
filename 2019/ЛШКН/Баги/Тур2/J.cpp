/*
	Problem J
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#ifdef LOCAL
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
	#define LASSERT(X) assert(X)
#else
    #define eprintf(...) 42
	#define LASSERT(X) 43
#endif

using ll = long long;
using ld = long double;
using D = double;
using uint = unsigned int;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

template <typename T>
T input() {
    T res;
    cin >> res;
    LASSERT(cin);
    return res;
}

template <typename IT>
void input_seq(IT b, IT e) {
    std::generate(b, e, input<typename std::remove_reference<decltype(*b)>::type>);
}

#define SZ(vec)         int((vec).size())
#define ALL(data)       (data).begin(),(data).end()
#define RALL(data)      (data).rbegin(),(data).rend()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

const int maxn = 100005;

pair2<int> p[maxn];
int n, m;

void solve()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &p[i].fi);
	for (int j = 0; j < n; j++) scanf("%d", &p[j].se);
	sort(p, p + n);
	int cursum = 0;
	int ans = 0;
	while (cursum + p[ans].se <= m)
	{
		cursum += p[ans].se;
		ans++;
	}
	printf("%d\n", ans);
}

int main()
{
	int NT;
	scanf("%d", &NT);
	for (int T = 0; T < NT; T++)
	{
		printf("Case %d: ", T + 1);
		solve();
	}
    return 0;
}
