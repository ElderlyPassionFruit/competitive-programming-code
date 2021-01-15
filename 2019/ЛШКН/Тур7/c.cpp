#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int t, type;
};

bool operator<(event a, event b) {
	return a.t < b.t;
}

int n, k, q;
vector<event> help;
void read() {
	cin >> n >> k >> q;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		help.push_back({l, 1});
		help.push_back({r + 1, -1});
	}
}

vector<int> ans;
const int MAXN = 2e5 + 10;
int pref[MAXN];


void run() {
	int cnt = 0;
	sort(help.begin(), help.end());
	int pos = 0;
	for (int i = 0; i < MAXN; i++) {
		while (pos < help.size() && help[pos].t == i) {
			cnt += help[pos].type;
			pos++;
		}
		pref[i] = pref[i - 1];
		if (cnt >= k)
			pref[i]++;
	}

	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		ans.push_back(pref[b] - pref[a - 1]);
	}
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