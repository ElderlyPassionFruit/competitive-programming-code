#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, q;

void read() {
	cin >> n >> q;
}

unordered_map<int, unordered_map<int, int> > have;
const int MAXC = 200;

void build() {
	for (int i = -100; i <= 200; i++) {
		for (int j = -200; j <= 0; j++) {
			have[i][j] = j;
			if (j > 0) have[i][j] = 0;
		}
	}
}

void solve(int x, int d, int l) {
	unordered_map<int, unordered_map<int, int> > n_have = have;
	for (int i = -100; i <= 200; i++) {
		for (int j = -200; j <= 0; j++) {
			if (d == 1) {
				if (i - j < x) {
					n_have[i + l][j + l] = have[i][j];
					if (j + l > 0) n_have[i + l][j + l] = 0;
				}
			}
			else {
				if (i + j >= x) {
					n_have[i - l][j + l] = have[i][j];
					//if (j + l > 0) n_have[i - l][j + l] = 0;
				}
			}
		}
	}
	have = n_have;
}

vector<int> ans;

void make_ans() {
	for (int i = 0; i < n; i++)
		ans.push_back(abs(have[i][0]));
}

void run() {
	build();
	/*for (int i = 1; i >= -9; i--) {
		for (int j = 0; j < 10; j++) {
			cout << have[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	while (q--) {
		int x, d, l;
		cin >> x >> d >> l;
		solve(x, d, l);

		/*for (int i = 1; i >= -9; i--) {
		for (int j = 0; j < 10; j++) {
			cout << have[j][i] << " ";
		}
		cout << endl;
		}
		cout << endl;*/
	}


	
	make_ans();
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