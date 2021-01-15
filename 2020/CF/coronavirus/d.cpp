#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, x;
vector<int> a;

void read() {
	cin >> n >> x;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	for (int i = 0; i < n; i++)
		a.push_back(a[i]);
}

int get(int x) {
	if (x <= 0) return 0;
	return x * (x + 1) / 2;
}

int get(int l, int r) {
	return get(r) - get(l - 1);
}

int ans;

void run() {
	/*cout << "a = " << endl;
	for (auto i : a) {
		cout << i << " ";
	}*/
	//cout << endl;
	ans = 0;
	int pos = 2 * n - 1;
	int fans = 0;
	int sum = 0;
	for (int i = 2 * n - 1; i >= n; i--) {
		while (pos >= 0 && sum + a[pos] <= x) {
			sum += a[pos];
			fans += get(a[pos]);
			pos--;
		}
		int add = 0;
		if (sum < x) {
			assert(pos >= 0);
			//cout << "l = " << a[pos] - (x - sum) + 1 << " r = " << a[pos] << endl;
			add = get(a[pos] - (x - sum) + 1, a[pos]);
		}
		//cout << "i = " << i << " pos = " << pos << " sum = " << sum << " fans = " << fans << " add = " << add << endl;
		/*if (fans + add == 6) {
			cout << i << " " << pos << endl;
		}*/
		chkmax(ans, fans + add);
		if (pos == i) {
			pos--;
			sum = 0;
			fans = 0;
		} else {
			sum -= a[i];
			fans -= get(a[i]);
		}
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}