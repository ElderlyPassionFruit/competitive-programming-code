#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

const int MAXN = 2510;
vector<int> g[MAXN];

int sz1, sz2;

int ans;

void build() {
	vector<string> L, R;
	string l = "";
	l += s[0];
	l += s[1];
	string r = "";
	r += s[n - 2];
	r += s[n - 1];
	ans = 1 + (l != r);
	
	for (int i = 1; i < n; i++) {
		string x = "";
		x += s[i - 1];
		x += s[i];
		if (x == l || x == r) continue;
		if (i % 2)
			L.push_back(x);
		else
			R.push_back(x);
	}

	sort(all(L));
	L.resize(unique(all(L)) - L.begin());
	sort(all(R));
	R.resize(unique(all(R)) - R.begin());

	/*cout << "L = " << endl;
	for (auto i : L)
		cout << i << " ";
	cout << endl;

	cout << "R = " << endl;
	for (auto i : R) 
		cout << i << " ";
	cout << endl;*/

	sz1 = L.size();
	sz2 = R.size();

	for (int i = 1; i + 1 < n; i++) {
		string x = "";
		x += s[i - 1];
		x += s[i];
		string y = "";
		y += s[i];
		y += s[i + 1];
		if (l == x || l == y || r == x || r == y) continue;
		if (i % 2 == 0) {
			swap(x, y);
		}
		int v, u;
		v = lower_bound(all(L), x) - L.begin();
		u = lower_bound(all(R), y) - R.begin();
		
		g[v].push_back(u);
	}
	for (int i = 0; i < sz1; i++) {
		sort(all(g[i]));
		g[i].resize(unique(all(g[i])) - g[i].begin());
	}
}

int used[MAXN];
int mt[MAXN];

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v]) {
		if (mt[i] == -1) {
			mt[i] = v;
			return true;
		}
	}
	for (auto i : g[v]) {
		if (dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

void calc() {
	for (int v = 0; v < sz1; v++)
		used[v] = -1;
	for (int v = 0; v < sz2; v++)
		mt[v] = -1;
	int c = 0;
	for (int i = 0; i < sz1; i++) {
		dfs(i, c++);
	}
}

void make_ans() {
	/*cout << "g = " << endl;
	for (int i = 0; i < sz; i++) {
		cout << "i = " << i << endl;
		for (auto v : g[i])
			cout << v << " ";
		cout << endl;
	}
	cout << endl;*/
	int fans = 0;
	for (int i = 0; i < sz2; i++)
		fans += (mt[i] != -1);
	//cout << fans << endl;
	ans += fans;
}

void run() {
	build();
	calc();
	make_ans();
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