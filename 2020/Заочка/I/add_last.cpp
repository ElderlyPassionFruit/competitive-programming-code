#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ull
int n;

void read() {
	cin >> n;
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

int len(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

void run() {
	vector<int> now;
	for (int i = 1; i < 10; i++)
		now.push_back(i);

	vector<int> now1;
	for (int i = 10; i < 100; i++) {
		if (check(i))
		now1.push_back(i);
	}
	vector<int> now2;
	for (int i = 100; i < 1000; i++) {
		if (check(i))
		now2.push_back(i);
	}

	vector<int> pows(100, 1);
	for (int i = 1; i < 100; i++)
		pows[i] = pows[i - 1] * 10;

	int it = 1;
	while (now.size() || now1.size() || now2.size()) {
		vector<int> next;
		for (auto x : now)
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				for (int l = 1; l < 10; l++) {
					//l = 0;
					int nxt = x + j * pows[it] + k * pows[it + 1] + l * pows[it + 2];
					if (check(nxt))
						next.push_back(nxt);
					//l = 10;
				}
			}
		}
		now = now1;
		now1 = now2;
		now2 = next;
		sort(all(now2));
		now2.resize(unique(all(now2)) - now2.begin());

		cout << "now2 = " << endl;
		for (auto i : now2)
			cout << i << " ";
		cout << endl;
		cout << endl;
		if (now2.size()) {
			cout << "len = ";
			cout << len(now2.back()) << endl;
		}
		it++;
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