#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
struct event{
	int d, c, ind;
	vector<int> p;
	event() {}
	event(int x, int y, vector<int> z, int a) {
		d = x, c = y, p = z, ind = a;
	}
};

bool operator<(const event  & a, const event & b) {
	return a.d < b.d;
}

int n;
vector<int> used;
vector<event> a;
vector<int> p;

void dfs(int v) {
	used[v] = 1;
	for (auto i : a[v].p) {
		if (used[i] == 1) {
			cout << "NO" << endl;
			exit(0);
		}
		if (!used[i])
			dfs(i);
	}	
	used[v] = 2;
}

vector<int> ans;
int t;

void run(int pos) {
	used[pos] = true;
	for (auto i : a[pos].p) {
		if(used[p[i]]) continue;
		run(p[i]);
	}
	t += a[pos].c;
	if (t > a[pos].d) {
		cout << "NO" << endl;
		exit(0); 
	}
	ans.push_back(a[pos].ind);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	used.resize(n);
	a.resize(n);
	t = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i].d >> a[i].c;
		int r;
		cin >> r;
		a[i].p.resize(r);
		for (auto &j : a[i].p){
			cin >> j;
			j--;
		}
		a[i].ind = i;
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	used.assign(n, false);
	sort(a.begin(), a.end());
	p.resize(n);
	for (int i = 0; i < n; i++) {
		p[a[i].ind] = i;
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			run(i);
		}
	}

	cout << "YES" << endl;
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << endl;
	return 0;
}