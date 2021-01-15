#include <bits/stdc++.h>

using namespace std;
#define int long long

struct ed{
	int u, v, a, b;
	ed() {

	}
	ed(int x, int y, int z, int t) {
		u = x, v = y, a = z, b = t;
	}
};

vector<ed> g;
int n, m;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		g.push_back({a, b, c, d});
	}
}

const int MAXN = 3e5 + 10;
int pred[MAXN];

int get_pred(int v) {
	if (v == pred[v]) return v;
	return pred[v] = get_pred(pred[v]);
}

void union_set(int a, int b) {
	a = get_pred(a);
	b = get_pred(b);
	if (a == b) return;
	pred[a] = b;
}

void make() {
	for (int i = 0; i < n; i++) {
		pred[i] = i;
	}
}

int p, q;

void run() {
	make();
	p = 0;
	q = 0;
	vector<bool> used(m, false);
	for (int i = 0; i < n - 1; i++) {
		int p1 = 0, q1 = 1;
		int ind = -1;
		for (int j = 0; j < m; j++) {
			if (used[j]) continue;
			if (get_pred(g[j].u) != get_pred(g[j].v)) {
				if (p1 * (q + g[j].b) < q1 * (p + g[j].a)) {
					p1 = p + g[j].a;
					q1 = q + g[j].b;
					ind = j;
				}
			}
		}
		p = p1;
		q = q1;
		union_set(g[ind].u, g[ind].v);
		used[ind] = true;
	}
}

void write() {
	int ge = __gcd(p, q);
	p /= ge;
	q /= ge;
	cout << p << "/" << q << endl;
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