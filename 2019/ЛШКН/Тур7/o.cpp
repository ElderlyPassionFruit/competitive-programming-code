#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<pair <int, int> > get_prime(int k) {
	vector<pair <int, int> > ans;
	for (int i = 2; i * i <= k; i++) {
		if (k % i == 0) {
			int x = 0;
			while (k % i == 0) {
				k /= i;
				x++;
			}
			ans.push_back({i, x});
		}
	}
	if (k > 1)
		ans.push_back({k, 1});
	sort(ans.begin(), ans.end());
	return ans;
}

const int MAXK = 30;
int r[MAXK], have[MAXK], need[MAXK];

vector<int> ftree[MAXK];

int n, k;
vector<pair <int, int> > p;

void read() {
	cin >> n >> k;
	p = get_prime(k);
	for (int i = 0; i < p.size(); i++) {
		ftree[i].resize(n);
	}

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		for (int j = 0; j < p.size(); j++) {
			int a = 0;
			while (x % p[j].first == 0) {
				x /= p[j].first;
				a++;
			}
			ftree[j][i] = a;
			r[j] = 0, have[j] = 0, need[j] = p[j].second;
		}
	}
}


int get_cnt(int pos) {
	for (int i = 0; i < p.size(); i++) {
		while (r[i] < n && have[i] < need[i]) {
			have[i] += ftree[i][r[i]];
			r[i]++;
		}
	}

	for (int i = 0; i < p.size(); i++) {
		if (have[i] < need[i])
			return 0;
	}	
	int ans = pos + 1;
	for (int i = 0; i < p.size(); i++)
		chkmax(ans, r[i]);

	for (int i = 0; i < p.size(); i++) {
		have[i] -= ftree[i][pos];
		chkmax(have[i], 0);
		chkmax(r[i], pos + 1);
	}
	return n - ans + 1;
}

int ans = 0;

void run() {
	for (int i = 0; i < n; i++) {
		ans += get_cnt(i);
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