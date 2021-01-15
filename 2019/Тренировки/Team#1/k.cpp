//#pragma GCC optimize("SEX_ON_THE_BEACH")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,popcnt,tune=native")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rev(x) reverse(all(x))
#define pbc push_back
#define pob pop_back()
#define mx(x) *max_element(all(x))
#define mn(x) *min_element(all(x))
#define rall(x) x.rbegin(), x.rend()
#define vin(v) for(auto &i : v) cin >> i;
#define vout(v, c) for (auto &i : v) cout << i << c;
#define endl '\n'
#define gcd(a, b) __gcd(a, b)
#define pop_cnt(a) __builtin_popcount(a)

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template<typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(NULL));

const int inf = 1e9 + 10;
const ll INF = 1e18 + 10;
const int MAXN = 1e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

void yes() {
	cout << "YES\n";
	exit(0);
}

void no() {
	cout << "NO\n";
	exit(0);
}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
	//cout << n << "\n" << s << "\n";
}

bool check(string s) {
	int cnt = 0;
	for (int i = 1; i < n; i++)
		cnt += s[i] != s[i - 1];
	return cnt == 2;
}

bool check(vector<char> a) {
	string x1 = "", x2 = "";
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == a[0])
			cnt1++;
		if (s[i] == a[1])
			cnt2++;
		if (s[i] == a[2])
			cnt3++;
	}

	int pos = 0;
	int lett = 0;
	while (pos < n) {
		if (lett == 0 && cnt1 == x1.size())
			lett++;
		if (lett == 1 && cnt1 + cnt2 == x1.size())
			lett++;
		if (lett == 2 && cnt1 + cnt2 + cnt3 == x1.size())
			lett++;
		if (s[pos] == a[lett]) {
			x1 += s[pos];
		}
		else {
			x2 += s[pos];
		}
		pos++;
	}

	/*cout << "a = " << endl;
	for (auto i: a)
		cout << i << " ";
	cout << endl;

	cout << x1 << " " << x2 << endl;*/
	return check(x1 + x2) || check(x2 + x1);
}

bool ans;

void run() {
	set<char> have;
	for (auto i : s)
		have.insert(i);
	if (have.size() <= 2)
		yes();
	vector<char> a = {'R', 'G', 'B'};
	sort(all(a));
	do {
		if (check(a)) {
			ans = true;
			break;
		}
	} while (next_permutation(all(a)));
}

void write() {
	if (ans)
		yes();
	else
		no();
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