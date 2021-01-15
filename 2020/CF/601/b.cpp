#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int get(const vector<int> & b, int l, int r, int pos) {
	if (pos < l && pos >= r) return 1e18;
	int ans = 0;
	for (int i = l; i < r; i++) 
		ans += abs(pos - i) * b[i];
	return ans;
}

int get(int x) {
	vector<int> b = a;
	int cnt = 0;
	int l = 0;
	while (l < n) {
		while (l < n && b[l] == 0)
			l++;
		
		int r = l;
		int have = 0;
		int pos = -1;
		
		while (r < n && have < x) {
			have += b[r];
			if (have >= (x + 1) / 2 && pos == -1)
				pos = r;
			r++;
		}

 		if (r < n){
			b[r] += have % x;
			cnt += have % x;
			b[r - 1] -= have % x;
		}

		int fans = 1e18;
		chkmin(fans, get(b, l, r, pos));
		
		for (int i = 1; i < 10; i++) {
			chkmin(fans, get(b, l, r, pos + i));
			chkmin(fans, get(b, l, r, pos - i));
		}
		
		cnt += fans;
		l = r;
	}
	return cnt;
}

int ans;
const int INF = 1e18;
void run() {
	int sum = 0;
	for (auto i : a)
		sum += i;
	ans = INF;
	for (int i = 2; i * i <= sum; i++) {
		if (sum % i == 0) {
			chkmin(ans, get(i));
			while (sum % i == 0)
				sum /= i;
		}
	}
	if (sum != 1)
		chkmin(ans, get(sum));
}

void write() {
	if (ans != INF)
		cout << ans << endl;
	else
		cout << -1 << endl;
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