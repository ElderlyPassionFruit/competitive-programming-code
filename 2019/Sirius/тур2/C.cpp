#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e6 + 10;

struct line {
	int k, b;
	line () {
		k = 0, b = 1e18;
	}	
	line (int x, int y) {
		k = x, b = y;
	}
};

int eval(int x, line l) {
	return l.k * x + l.b;
}

line tree[MAXN * 4];
int dp1[MAXN], dp2[MAXN], h[MAXN], w[MAXN];
int n;
const int INF = 1e18;
void upd(line l, int v = 1, int tl = 0, int tr = MAXN) {
	int tm = (tl + tr) / 2;
	bool mid = eval(tl, tree[v]) > eval(tl, l);
	bool left = eval(tm, tree[v]) > eval(tm, l);
	
	if (mid) swap(l, tree[v]);
	if (tl == tr - 1)
		return;
	if (mid != left)
		upd(l, v * 2, tl, tm);
	else
		upd(l, v * 2 + 1, tm, tr);
}

int get(int x, int v = 1, int tl = 0, int tr = MAXN) {
	if (tl > x || tr <= x) return INF;
	if (tl == tr - 1) 
		return eval(x, tree[v]);
	int tm = (tl + tr) / 2;
	return min(eval(x, tree[v]), min(get(x, v * 2, tl, tm), get(x, v * 2 + 1, tm, tr)));
}

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
	}	
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
}

int pref[MAXN];

int sq(int x) {
	return x*x;
}

void wr() {
	for (int i = 0; i <= n; i++)
//		cout << dp[i] << " ";
	cout << endl;
}

void run() {
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1] + w[i];
	}

	dp1[1] = 0;
	for (int i = 2; i <= n; i++) {
		dp1[i] = INF;
		for (int j = 1; j < i; j++) {
			dp1[i] = min(dp1[i], dp1[j] + sq(h[i] - h[j]) + pref[i - 1] - pref[j]);
		}
	}
	//wr();
	dp2[1] = 0;
	upd(line(-2*h[1], sq(h[1]) + dp2[1] - pref[1]));
	for (int i = 2; i <= n; i++) {
		dp2[i] = get(h[i]) + sq(h[i]) + pref[i - 1];
		upd(line(-2*h[i], sq(h[i]) + dp2[i] - pref[i]));
	}
//	wr();
}

void write() {
}

void gen() {
	n = 8;
	for (int i = 0; i <= n; i++) {
		dp1[i] = 0, dp2[i] = 0, h[i] = 0, w[i] = 0, pref[i] = 0;
	}
	for (int i = 0; i < 10*n; i++) {
		tree[i] = line(0, INF);
	}
	for (int i = 1; i <= n; i++) {
		h[i] = rand() % 10;
		w[i] = rand() % 10;
	}


}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int i = 0;
	while(i + 1) {
		i++;
		gen();
		run();
		for (int j = 0; j <= n; j++)
			if (dp1[j] != dp2[j]) {
				cout << "WA " << i << endl;
				cout << n << endl;
				//cout << "h" << endl;
				for (int k = 1; k <= n; k++) cout << h[k] << " "; cout << endl;
				//cout << "w" << endl;
				for (int k = 1; k <= n; k++) cout << w[k] << " "; cout << endl;
				cout << "dp1" << endl;
				for (int k = 1; k <= n; k++) cout << dp1[k] << " "; cout << endl; 
				cout << "dp2" << endl;
				for (int k = 1; k <= n; k++) cout << dp2[k] << " "; cout << endl;
				return 0;
			}
		cout << "OK " << i << endl;
			/*		cout << n << endl;
				//cout << "h" << endl;
				for (int k = 1; k <= n; k++) cout << h[k] << " "; cout << endl;
				//cout << "w" << endl;
				for (int k = 1; k <= n; k++) cout << w[k] << " "; cout << endl;
				//cout << "dp1" << endl;
				for (int k = 1; k <= n; k++) cout << dp1[k] << " "; cout << endl; 
				//cout << "dp2" << endl;
				for (int k = 1; k <= n; k++) cout << dp2[k] << " "; cout << endl;
		cout << endl;
	*/}

	read();
	run();
	write();
	return 0;
}