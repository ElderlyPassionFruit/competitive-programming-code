#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;

void read() {
	cin >> n;
	if (n > 10) {
		cout << "NO";
		exit(0);
	}
}

bool check(int x) {
	int s = x;
	int sum = 0;
	while (s) {
		sum += s % 10;
		if (s % 10 == 0) return false;
		s /= 10;
		if (x % sum != 0) return false;
	}
	return true;
}

vector<int> get(int x) {
	vector<int> ans;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			while (x % i == 0) {
				x /= i;
				ans.push_back(i);
			}
		}
	}
	if (x != 1) {
		ans.push_back(x);
	}
	return ans;
}

int get_cnt(int x) {
	int ans = 0;
	while (x % 2 == 0) {
		x /= 2;
		ans++;
	}
	return ans;
}

string get_str(int x) {
	string ans = "";
	while (x) {
		ans += '0' + x % 10;
		x /= 10;
	}
	return ans;
}

void run() {
	int x = 1;
	for (int i = 0; i < n - 1; i++)
		x *= 10;
	//int ans = 1e9;
//	vector<string> a;

	vector<pair<int, int> > b;
	for (int i = x; i < x * 10; i++) {
		if (check(i)){
			b.emplace_back(get_cnt(i), i);
			/*a.push_back(get_str(i));
			auto fans = get(i);
			//if (fans.back() > 13)
			//	continue;
			cout << i << " primes: ";

			int f = 0;
			for (auto j : fans)
				cout << j << " ", chkmax(f, j);
			cout << endl;
			chkmin(ans, f);
			//return;*/
		}
	}
	/*cout << ans << endl;
	cout << endl;
	cout << "a = " << endl;
	sort(all(a));
	for (auto i : a) {
		reverse(all(i));
		cout << i << "\n";
	}
	cout << "cnt = " << a.size() << endl;*/

	vector<int> help;
	for (auto i : b)
		help.push_back(i.second);
	sort(all(help));
	for (auto i: help)
		cout << i << " ";
	cout << endl;

	sort(all(b));
	reverse(all(b));
	for (auto i : b) {
		cout << /*i.first << " " <<*/ i.second << " ";
		auto fans = get(i.second);
		for (auto j : fans)
			cout << j << " ";
		cout << "|" << " ";
		int sum = 0;
		while (i.second) {
			sum += i.second % 10;
			i.second /= 10;
			cout << sum << " "; 
		}
		cout << endl;
	}
}

void write() {

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