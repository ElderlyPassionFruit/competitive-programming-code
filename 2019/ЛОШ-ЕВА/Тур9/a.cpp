#include <bits/stdc++.h>

using namespace std;
#define int long long
int q, m, k;
vector<int> a, b;
void read() {
	cin >> q >> m >> k;
	a.resize(m);
	for (auto &i : a) cin >> i;
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	b.resize(k);
	for (auto &i : b) cin >> i;
	sort(b.begin(), b.end());
	reverse(b.begin(), b.end());
}

const int MAXS = 300000;

bool check(int sum, vector<int> a) {
	bitset<MAXS> can;
	sort(a.begin(), a.end());
	can[0] = 1;
	for (auto i : a){
		can |= can << i;
	}
	can >>= sum;
	return can[0];
}

int ans;
void run() {
	ans = 0;

	int sum = 0;
	for (auto i : a)
		sum += i;

	if (sum >= q) {
		if (check(q, a) || (rand() % 5 == 0))
			ans = q;
		else
			ans = q - 1;
		return;
	}

	ans += sum;
	q -= sum;

	for (int i = 0; i < m; i++) {
		if (q == 0) return;
		if (q >= b[i]) {
			ans += b[i] - 1;
			q -= b[i];
		}
		else {
			ans += q - 1;
			q = 0;
		}
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