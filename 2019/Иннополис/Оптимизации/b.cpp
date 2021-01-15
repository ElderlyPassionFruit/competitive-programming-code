#include <bits/stdc++.h>

using namespace std;

#define int long long
const int INF = -1e18;

struct line {
	int k, b;
	line() {
 		k = 0;
 		b = INF;
	}
	line(int k1, int b1) {
		k = k1;
		b = b1;
	}
};

int eval(line a, int x) {
	return a.k * x + a.b;
}

const int MAXN = 1e6 + 10;
line tree[4 * MAXN];
int dp[MAXN], a[MAXN], d[MAXN];
int n;

void upd(line val, int v = 1, int tl = 0, int tr = n + 2) {
	int tm = (tl + tr) / 2;
	bool left = eval(tree[v], tl) < eval(val, tl);
	bool mid = eval(tree[v], tm) < eval(val, tm);
	/*cout << "upd: " << endl;
	cout << val.k << " " << val.b << endl;
	cout << left << " " << mid << endl;
	cout << endl;
	*/if (mid) 
		swap(val, tree[v]);
	if (tl == tr - 1)
	{
		return;
	}
	if (left != mid)
		upd(val, v * 2, tl, tm);
	else
		upd(val, v * 2 + 1, tm, tr);
}

int get(int pos, int v = 1, int tl = 0, int tr = n + 2){
	if (tl > pos || tr <= pos)
		return INF;
	if (tl == tr - 1)
		return eval(tree[v], pos);
	int tm = (tl + tr) / 2;
	return max(eval(tree[v], pos), max(get(pos, v * 2, tl, tm), get(pos, v * 2 + 1, tm, tr)));
}

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> d[i];	
}

void wr(int v = 1, int tl = 0, int tr = n + 2) {
	cout << "v = " << v << " tl = " << tl << " tr = " << tr << " y = " << tree[v].k << " * x + " << tree[v].b << endl;
	if (tl == tr - 1)
		return;
	int tm = (tl + tr) / 2;
	wr(v * 2, tl, tm);
	wr(v * 2 + 1, tm, tr);
}

void run() {
	dp[0] = 0;
	dp[1] = 0;
	upd(line(-d[1], dp[1] + 1*d[1] + a[1]));
	for (int i = 2; i <= n + 1; i++) {
		dp[i] = max(0LL, get(i));
		upd(line(-d[i], dp[i] + i*d[i] + a[i]));
	}
	/*for (int i = 2; i <= n + 1; i++) {
		for (int j = 1; j < i; j++) {
			dp[i] = max(dp[i], dp[j] - (i - j) * d[j] + a[j]);
		}
	}*/
}

void write() {
/*	for (int i = 0; i <= n + 1; i++)
		cout << dp[i] << " ";
	cout << endl; 
*/	cout << dp[n + 1] << endl; 
//	wr();
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