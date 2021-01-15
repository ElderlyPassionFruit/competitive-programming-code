#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, q;

void read() {
	cin >> n >> m >> q;
}

const int MAXN = 1e5 + 10;

map<int, int> Next[MAXN];

void build() {

}

void upd(int a, int b, int x) {
	//for (; x < m; x++)
	if (!Next[a].count(x))
		Next[a][x] = a;
	if (!Next[b].count(x))
		Next[b][x] = b;
	swap(Next[a][x], Next[b][x]);
} 

int get(int pos, int x) {
	for (int i = 0; i < x; i++){
		if (Next[pos].count(i))
			pos = Next[pos][i];
	}
	return pos;
}

void wr() {
	cout << "table = " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << Next[j][i] << " ";
		}
		cout << endl;
	}
}
 
vector<int> ans;

void run() {
	build();
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 0) {
			int a, b, x;
			cin >> a >> b >> x;
			a--;
			b--;
			x--;
			upd(a, b, x);
		}
		if (type == 1) {
			int pos, x;
			cin >> pos >> x;
			pos--;
			ans.push_back(get(pos, x));
		}
		//wr();
	}
}

void write() {
	for (auto i : ans)
		cout << i + 1 << "\n";
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