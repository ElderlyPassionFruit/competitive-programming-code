#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, q;
const int MAXN = 3 * 1e5 + 10;
vector <int> now;
void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		char x;
		cin >> x;
		now.push_back(x - '0');
	}
}

int len[MAXN];
int sum = 0;


void build() {
	for (int i = 0; i < n; i++) {
		if (now[i] == 0)
			continue;
		int j;
		for (j = i; j < n; j++) {
			if (now[j] == 0) {
				break;
			}
		}
		j--;
		for (int k = i; k <= j; k++) {
			sum -= len[k];
			len[k] = max(len[k], j - k + 1);
			sum += len[k];
		}
		i = j + 1;
	}
}

void upd(int l, int r, int c) {
	for (int i = l; i <= r; i++) {
		now[i] = c;
	}
	for (int i = 0; i < n; i++) {
		if (now[i] == 0)
			continue;
		int j;
		for (j = i; j < n; j++) {
			if (now[j] == 0) {
				break;
			}
		}
		j--;
		for (int k = i; k <= j; k++) {
			sum -= len[k];
			len[k] = max(len[k], j - k + 1);
			sum += len[k];
		}
		i = j + 1;
	}
}

int solve() {
	int ans = 0;
	ans = sum;
	return ans;
}

vector <int> ans;
void run() {
	build();
	ans.push_back(solve());
	for (int test = 0; test < q; test++) {
		int l, r, c;
		cin >> l >> r >> c;
		l--;
		r--;
		upd(l, r, c);
 		ans.push_back(solve());
	}
}

void write() {
	for (auto i : ans) {
		cout << i << '\n';
	}
}

signed main() {
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}