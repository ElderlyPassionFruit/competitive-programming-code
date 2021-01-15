#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ull

const int base = 1e18;

struct lnum{
	int x0, x1, x2;
	lnum() {
		x0 = 0, x1 = 0, x2 = 0;
	};
	lnum(string s) {
		x0 = 0, x1 = 0, x2 = 0;
		//reverse(all(s));
		for (auto i : s) {
			x0 *= 10;
			x0 += i - '0';
			x1 += x0 / base;
			x0 %= base;
			x2 += x1 / base;
			x1 %= base;
		}	
	}
};

lnum operator+(const lnum & a, const lnum & b) {
	lnum ans;
	ans.x0 = a.x0 + b.x0;
	ans.x1 = a.x1 + b.x1;
	ans.x2 = a.x2 + b.x2;
	ans.x1 += ans.x0 / base;
	ans.x0 %= base;
	ans.x2 += ans.x1 / base;
	ans.x1 %= base;
	return ans;
}

lnum operator^(const lnum & a, const int p) {
	lnum ans = a;
	for (int i = 0; i < p; i++) {
		ans.x0 *= 10;
		ans.x1 += ans.x0 / base;
		ans.x0 %= base;
		ans.x2 += ans.x1 / base;
		ans.x1 %= base;
	}
	return ans;
}

int get_len(lnum x) {
	int ans = 0;
	while (x.x1 + x.x2 + x.x0) {
		ans++;
		//x /= 10;
	}
	return ans;
}

//bool check(lnum x, int d) {
	
//}

bool check(lnum x) {
	lnum s = x;
	int sum = 0;
	while (s.x0 + s.x1 + s.x2) {
		if (s.x0 % 10 == 0) return false;
		sum += s.x0 % 10;
		s.x0 /= 10;
		s.x1 += (s.x2 % 10) * (base / 10);
		s.x2 /= 10;
		//s.x
		//if (!check(x, sum)) return false;
	}
	return true;
}

string to_str(int x) {
	string ans = "";
	while (x) {
		ans += '0' + x % 10;
		x /= 10;
	}
	return ans;
}

int get_len(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

int pows[20];

void build() {
	pows[0] = 1;
	for (int i = 1; i < 20; i++)
		pows[i] = pows[i - 1] * 10;
}

bool check(int x) {
	int s = x;
	int sum = 0;
	while (s) {
		if (s % 10 == 0) return false;
		sum += s % 10;
		s /= 10;
		if (x % sum) return false;
	}
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();

	int start = 82212122112;
	//int start = 62112;
	int len = get_len(start);
	int p = pows[len];
	vector<string> ans;
	for (int i = 1; i < 1e8; i++) {
		int x = start + p * i;
		if (check(x)) {
			ans.push_back(to_str(x));
		}
	}
	//cout << "p = " << p << endl;
	map<char, int> cnt;
	int mx_len = 0;
	for (auto i : ans) {
		if (i.size() <= len) {
			cout << i << endl;
		}
		assert(i.size() > len);
		cnt[i[len]]++;
		chkmax(mx_len, i.size());
	}

	sort(all(ans));
	for (auto i : ans) {
		cout << i << endl;
	}
	cout << "sz = " << ans.size() << endl;

	cout << "cnt = " << endl;
	for (auto i : cnt)
		cout << i.first << " " << i.second << endl;
	cout << endl;
	cout << "mx_len = " << mx_len << endl;
	return 0;
}