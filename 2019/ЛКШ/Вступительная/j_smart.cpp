#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e3 + 10;
const int MOD = 1e9 + 7;
int fact[MAXN], pows[MAXN][2];
int n, k;
set <int> g[MAXN];

void make() {
	pows[0][0] = 1;
	pows[0][1] = 1;
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i][0] = pows[i - 1][0] * k;
		pows[i][0] %= MOD;
		pows[i][1] = pows[i - 1][1] * (k - 1);
		pows[i][1] %= MOD;
		fact[i] = fact[i - 1] * i;
		fact[i] %= MOD;
	}
}

int mul(int a, int b) {
	return a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 0) {
		int x = binpow(a, n / 2);
		return mul(x, x);
	}
	else {
		int x = binpow(a, n - 1);
		return mul(a, x);
	}
}

int DIV(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

int c_n_k(int n, int k) {
	return DIV(fact[n], mul(fact[k], fact[n - k]));
}

int get_ans(int c1, int c2) {
	if (c2 == 0) {
		return mul(k, pows[c1 - 1][1]);
	}

	int ans;
	ans = pows[c1 - c2][1];
	int fans = 0;
	vector <int> h = {1, -1};
	//cout << endl;
	//cout << "c1 = " << c1 << " c2 = " << c2 << endl;
	//cout << "pol = " << endl;
	for (int i = 0; i <= c2 - 2; i++) {
	//	cout << h[i % 2] << " * " << c_n_k(c2, i) << " * " << pows[c2 - i][0] << " + ";   
		fans += h[i % 2] * pows[c2 - i][0] * c_n_k(c2, i) % MOD;
		fans %= MOD;
		fans += MOD;
		fans %= MOD;
	}
	//cout << h[(c2 - 1) % 2] << " * " << c2 - 1 << " * " << pows[1][0] << endl;
	fans += h[(c2 - 1) % 2] * pows[1][0] * (c2 - 1);
	fans %= MOD;
	fans += MOD;
	fans %= MOD;

	ans = mul(ans, fans);
	return ans;
}

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		p--;
		if (p == i)
			continue;
		g[i].insert(p);
		g[p].insert(i);
	}

	/*cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << i << " ";
		for (auto j : g[i]) {
			cout << j << " ";
		}
		cout << endl;
	}*/
	make();
}

int pred[MAXN];
bool used[MAXN];

int cnt, cnt_full;
bool flag;

void dfs(int v, int p) {
	//cout << "v = " << v << endl;
	used[v] = true;
	pred[v] = p;
	cnt_full++;
	for (auto i : g[v]) {
		if (i == p)
			continue;

		if (!used[i]) {
			dfs(i, v);
		}
		else {
			if (!flag) {
				flag = true;
				cnt = 1;
				int u = v;
				while (u != i) {
					u = pred[u];
					cnt++;
				}
			}
		}
	}	
}

int ans;
void run() {
	for (int i = 0; i < MAXN; i++)
		pred[i] = -1;

	ans = 1;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			cnt = 0;
			cnt_full = 0;
			flag = false;
			dfs(i, -1);
			//cout << "cnt_full = " << cnt_full << " cnt = " << cnt << endl; 
			ans *= get_ans(cnt_full, cnt);
			ans %= MOD;
		}
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}