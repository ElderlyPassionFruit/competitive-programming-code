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
	void relax() {
		x1 += x0 / base;
		x0 %= base;
		x2 += x1 / base;
		x1 %= base;
	}
	lnum(string s) {
		x0 = 0, x1 = 0, x2 = 0;
		for (auto i : s) {
			x0 *= 10;
			x1 *= 10;
			x2 *= 10;
			relax();
			x0 += i - '0';
		}
	}
	lnum(int x) {
		x0 = x;
		x1 = 0, x2 = 0;
	}
};

bool operator==(const lnum & a, const lnum & b) {
	return tie(a.x0, a.x1, a.x2) == tie(b.x0, b.x1, b.x2);
}

int pows[20];

void build() {
	pows[0] = 1;
	for (int i = 1; i < 20; i++)
		pows[i] = pows[i - 1] * 10;
}

lnum add(lnum ans, int len, int x) {
	if (len < 18) {
		ans.x0 += pows[len] * x;
		ans.relax();
		return ans;
	}
	len -= 18;
	if (len < 18) {
		ans.x1 += pows[len] * x;
		ans.relax();
		return ans;
	}
	len -= 18;
	assert(len < 18);
	ans.x2 += pows[len] * x;
	ans.relax();
	return ans;
}

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}

int add(int a, int b, int mod) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int mul(int a, int b, int mod) {
	return a * b % mod;
}

int operator%(lnum a, int b) {
	int mod = 0;
	int p = 1;
	while (a.x0 + a.x1 + a.x2) {
		mod = add(mod, mul(a.x0 % 10, p, b), b);
		p = mul(p, 10, b); 
		a.x0 /= 10;
		a.x0 += (a.x1 % 10) * pows[17];
		a.x1 /= 10;
		a.x1 += (a.x2 % 10) * pows[17];
		a.x2 /= 10;
	}
	return mod;
}

int NEED;
int INF;

lnum solve(lnum ans, int SUM, int LCM, int LEN) {
	if (LCM > INF) return lnum(0);
	if (SUM > 300) return lnum(0);
	if (LEN == NEED) {
		if (ans % LCM == 0) {
			return ans;
		}
		else {
			return lnum(0);
		}
	}	
	for (int i = 1; i <= 9; i++) {
		if ((SUM + i) % 5 == 0) continue;
		lnum x = solve(add(ans, LEN, i), SUM + i, lcm(LCM, SUM + i), LEN + 1);
		if (x == lnum(0)) continue;
		return x;
	}
	return lnum(0);
}

string to_str(lnum a) {
	string ans = "";
	while (a.x0 + a.x1 + a.x2) {
		ans += '0' + a.x0 % 10;
		a.x0 /= 10;
		a.x0 += (a.x1 % 10) * pows[17];
		a.x1 /= 10;
		a.x1 += (a.x2 % 10) * pows[17];
		a.x2 /= 10;	
	}
	reverse(all(ans));
	return ans;
}

int get_sum(lnum a) {
	int ans = 0;
	while (a.x0 + a.x1 + a.x2) {
		ans += a.x0 % 10;
		a.x0 /= 10;
		a.x0 += (a.x1 % 10) * pows[17];
		a.x1 /= 10;
		a.x1 += (a.x2 % 10) * pows[17];
		a.x2 /= 10;	
	}
	return ans;
}

int get_len(lnum a) {
	int ans = 0;
	while (a.x0 + a.x1 + a.x2) {
		ans++;
		a.x0 /= 10;
		a.x0 += (a.x1 % 10) * pows[17];
		a.x1 /= 10;
		a.x1 += (a.x2 % 10) * pows[17];
		a.x2 /= 10;	
	}
	return ans;
}

int get_lcm(lnum a) {
	int ans = 1;
	int sum = 0;
	while (a.x0 + a.x1 + a.x2) {
		sum += a.x0 % 10;
		ans = lcm(ans, sum);
		a.x0 /= 10;
		a.x0 += (a.x1 % 10) * pows[17];
		a.x1 /= 10;
		a.x1 += (a.x2 % 10) * pows[17];
		a.x2 /= 10;		
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	lnum x = lnum("58623511211121221221112112");
	//lnum x = lnum("21312125708815403242887936");
	cout << to_str(x) << " ";
	cout << endl;
	int len = 54;
	NEED = len;
	INF = 1e9;
	lnum ans = solve(x, get_sum(x), get_lcm(x), get_len(x));
	cout << "ans = " << endl;
	cout << ans.x0 << " " << ans.x1 << " " << ans.x2 << endl;
	cout << len << " " << to_str(ans) << endl;
	return 0;
}