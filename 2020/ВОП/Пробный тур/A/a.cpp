#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int block = 18;
const int base = pow(10LL, block);

struct BigInt{
	int flag;
	vector<int> num;

	BigInt() {
		flag = 0;
		num = {};
	}

	BigInt(int _flag, vector<int> _num) {
		flag = _flag;
		num = _num;
	}

	void relax() {
		for (int i = 0; i + 1 < (int)num.size(); i++) {
			num[i + 1] += num[i] >= 0 ? num[i] / base : (num[i] - base + 1) / base;
			num[i] = (num[i] % base + base) % base;
		}
		while (!num.empty() && num.back() == 0) {
			num.pop_back();
		}
	}

	void read() {
		string s;
		cin >> s;
		assert(!s.empty());
		reverse(all(s));
		flag = s.back() == '-';
		if (flag) s.pop_back();
		while (s.size() % block) s += "0";
		for (int i = (int)s.size() - 1; i >= 0; i--) {
			if ((i + 1) % block == 0) {
				num.push_back(s[i] - '0');
			} else {
				num[num.size() - 1] *= 10;
				num[num.size() - 1] += s[i] - '0';
			}
		}
		reverse(all(num));
		relax();
	}

	string write() {
		relax();
		if (num.empty()) {
			return "0";	
		}
		string ans = "";
		for (auto i : num) {
			string fans = "";
			for (int pos = 0; pos < block; pos++) {
				fans += '0' + i % 10;
				i /= 10;
			}
			ans += fans;
		}
		while (ans.back() == '0') ans.pop_back();
		if (flag) {
			ans += "-";
		}
		reverse(all(ans));
		return ans;
	}
};

BigInt operator+(const BigInt & a, const BigInt & b) {
	if (a.num.empty()) return b;
	if (b.num.empty()) return a;
	BigInt ans;
	for (int i = 0; i < (int)max(a.num.size(), b.num.size()); i++) {
		int nxt = 0;
		if (i < a.num.size()) nxt += a.flag ? -a.num[i] : a.num[i];
		if (i < b.num.size()) nxt += b.flag ? -b.num[i] : b.num[i];
		ans.num.push_back(nxt);
	}
	ans.num.push_back(0);
	ans.relax();
	if (ans.num.empty() || ans.num.back() > 0) {
		ans.flag = 0;
	} else {
		ans.flag = 1;
		for (auto &i : ans.num) i = -i;
		ans.relax();
	}
	return ans;
}

BigInt operator-(const BigInt & a, const BigInt & b) {
	return a + BigInt(b.flag ^ 1, b.num);
}

BigInt a, b;

void read() {
	a.read();
	b.read();
}

BigInt ans;

void run() {
	ans = a + b;
}

void write() {
	cout << ans.write() << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}