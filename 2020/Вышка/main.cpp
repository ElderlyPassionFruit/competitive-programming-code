#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int good[MAXN];
set<int> bad[MAXN];
vector<int> var[MAXN];

void make() {
	for (int i = 0; i < MAXN; i++)
		good[i] = i, var[i] = {i};
}

int get(int v) {
	if (v == good[v]) return v;
	return good[v] = get(good[v]);
}

void uni(int v, int u) {
	int a = get(v);
	int b = get(u);
	if (a == b) return;
	if (bad[a].size() < bad[b].size()) swap(a, b);
	for (auto i : bad[b]) { 
		bad[a].insert(get(i));
	}
	good[b] = a;
}

int n, k;

bool check(int v, int u) {
	return bad[v].count(u) || bad[u].count(v);
}


void read() {
	cin >> n >> k;
}

vector<char> ans;

void run() {
	make();
	for (int i = 0; i < k; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			int u, v;
			cin >> u >> v;
			uni(u, v);
		}
		else if (type == '-') {
			int u, v;
			cin >> u >> v;
			bad[get(u)].insert(get(v));
			bad[get(v)].insert(get(u));
		}
		else {
			int u, v;
			cin >> u >> v;
			if (get(v) == get(u)) {
				ans.push_back('+');
			}
			else if (check(get(v), get(u))) {
				ans.push_back('-');
			}
			else {
				ans.push_back('?');
			}
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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