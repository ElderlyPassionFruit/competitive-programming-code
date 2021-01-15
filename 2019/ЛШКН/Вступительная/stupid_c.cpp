#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e9 + 10;
struct e{
	int c, r, t;
	e() {
		c = 0, r = INF, t = INF;
	}
};

int n, t;
vector <e> a;
void read() {
	cin >> n >> t;
	for (int i = 0; i < n; i++) {
		e help;
		cin >> help.c >> help.r >> help.t;
		a.push_back(help);
	}
}

bool check(vector <int> help){
	int t_max = 0;
	int t_now = 0;
	for (int i = 0; i < n; i++) {
		t_now += a[i].t + a[i].r * help[i];
		if (help[i])
			t_max = t_now;
	}
	return t_max <= t;
}

int ans;
void run() {
	for (int i = 0; i <= n; i++) {
		vector <int> help(n, 0);
		for (int j = 0; j < i; j++)
			help[n - 1 - j] = 1;
		do{
			if (check(help)) {
				int fans = 0;
				for (int j = 0; j < n; j++)
						fans += a[j].c * help[j];
				ans = max(ans, fans);
			}
		} while(next_permutation(help.begin(), help.end()));
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