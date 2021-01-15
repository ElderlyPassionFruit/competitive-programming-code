#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m, q;
const int MAXN = 2 * 1e5 + 10;
int per[MAXN];
int arr[MAXN];
map <int, int> need_next;
map <int, int> need_pred;
void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		cin >> per[i];
	}
	
	for (int i = 0; i < n; i++) {
		need_next[per[i]] = per[(i + 1) % n];
		need_pred[per[(i + 1) % n]] = per[i];
	}

	for (int i = 0; i < m; i++) {
		cin >> arr[i];
	}
}


int last_right[MAXN];

int last_left[MAXN];
int help_len[MAXN];
int last_pos[MAXN];
int last_num[MAXN];

void wr() {
	cout << "last_left = ";
	for (int i = 0; i < m; i++) {
		cout << last_left[i] << " ";
	}
	cout << endl;
	cout << "last_right = ";
	for (int i = 0; i < m; i++) {
		cout << last_right[i] << " ";
	}
	cout << endl;
	cout << "help_len = ";
	for (int i = 0; i < m; i++) {
		cout << help_len[i] << " ";
	}
	cout << endl;
	cout << "last_num = ";
	for (int i = 0; i < m; i++) {
		cout << last_num[i] << " ";
	}
	cout << endl;
}


void make() {
	for (int i = 0; i < m; i++) {
		last_right[i] = 1e9;
		last_pos[i] = 1e9;
	}

	for (int i = m - 1; i >= 0; i--) {
		int need = need_next[arr[i]];
		last_right[i] = last_pos[need];
		last_pos[arr[i]] = i;
	}

	for (int i = 0; i < m; i++) {
		last_left[i] = -1e9;
	}
	for (int i = 0; i < m; i++) {
		int need = need_pred[arr[i]];
		last_left[i] = last_pos[need];
		last_pos[arr[i]] = i;
		if (last_left[i] != -1e9) {
			help_len[i] = help_len[last_left[i]] + 1;	
		}
		else {
			help_len[i] = 1;
		}
		if (help_len[i] > n) {
			last_num[i] = last_right[i];
		}
		else {
			if (last_left[i] != -1e9) {
				last_num[i] = last_right[last_num[last_left[i]]];
			}
			else {
				last_num[i] = i;
			}
		}
	}
}

string ans = "";

char get(int l, int r) {
	return '1';
}

void run() {
	make();
	wr();
	exit(0);
	for (int test = 0; test < q; test++) {
		int l,  r;
		cin >> l >> r;
		char ax;
		ax = get(l, r);
		ans += ax;
	}
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