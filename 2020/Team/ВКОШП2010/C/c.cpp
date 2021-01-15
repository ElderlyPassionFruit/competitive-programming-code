#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

struct flnum{
	int prime, cnt;
	flnum() {
		prime = 0, cnt = 0;
	}
	flnum(int a, int b) {
		prime = a, cnt = b;
	}
};

bool operator<(const flnum & a, const flnum & b) {
	return tie(a.prime, a.cnt) < tie(b.prime, b.cnt);
}

bool operator==(const flnum & a, const flnum & b) {
	return tie(a.prime, a.cnt) == tie(b.prime, b.cnt);
}

vector<flnum> merge(vector<flnum> a, vector<flnum> b) {
	for (auto i : b)
		a.push_back(i);
	sort(all(a));
	if (a.empty()) return a;
	vector<flnum> x;
	x.push_back(a[0]);
	for (int i = 1; i < (int) a.size(); i++) {
		if (x.back().prime == a[i].prime) {
			x[x.size() - 1].cnt += a[i].cnt;
		}
		else {
			x.push_back(a[i]);
		}
	}
	a = x;
	x.clear();
	for (auto i : a) {
		if (i.cnt != 0)
			x.push_back(i);
	}
	return x;
}

struct lnum{
	bool zero;
	bool minus;
	vector<flnum> primes;
	lnum() {
		zero = true;
		minus = false;
		primes = {};
	}
	lnum(int x) {
		zero = true;
		minus = false;
		primes = {};
		
		if (x == 0) {
			zero = true;
			return;
		}
		zero = false;
		if (x < 0) {
			minus = true;
		}
		x = abs(x);
		for (int i = 2; i * i <= x; i++) {
			if (x % i == 0) {
				primes.push_back({i, 0});
				while (x % i == 0) {
					primes[primes.size() - 1].cnt++;
					x /= i;
				}
			}
		}
		if (x > 1)
			primes.push_back({x, 1});
	}
};

bool operator==(const lnum & a, const lnum & b) {
	if (a.zero != b.zero) return false;
	if (a.zero && b.zero) return true;
	if (a.minus != b.minus) return false;
	return a.primes == b.primes;
}

lnum get_plus(int a, int b) {
	return lnum(a + b);
}

lnum get_minus(int a, int b) {
	return lnum(a - b);
}

lnum get_mul(int a, int b) {
	return lnum(a * b);
}

lnum get_div(int a, int b) {
	lnum A(a), B(b);
	for (auto &i : B.primes)
		i.cnt *= -1;
	A.minus ^= B.minus;
	A.primes = merge(A.primes, B.primes);
	return A;
}

lnum get_pow(int a, int b) {
	if (b == 0) return lnum(1);
	lnum ans(a);
	if (a < 0 && abs(b) % 2 == 0)
		ans.minus = false;
	for (auto &i : ans.primes)
		i.cnt *= b;
	return ans;
}

vector<lnum> nums;

void add(lnum x) {
	for (auto i : nums) if (i == x) return;
	nums.push_back(x);
}

int smart(int a, int b) {
	nums.clear();
	add(get_plus(a, b));
	add(get_minus(a, b));
	add(get_minus(b, a));
	add(get_mul(a, b));
	if (b != 0) {
		add(get_div(a, b));
	}
	if (a != 0) {
		add(get_div(b, a));
	}
	if (a != 0 || (a == 0 && b > 0))
		add(get_pow(a, b));
	if (b != 0 || (b == 0 && a > 0))
		add(get_pow(b, a));
	/*for (auto i : nums) {
		cout << "x = " << endl;
		cout << i.zero << " " << i.minus << endl;
		for (auto j : i.primes)
			cout << j.prime << " " << j.cnt << endl;
		cout << endl;
 	}*/
	return nums.size();
}


vector<ld> have;
const ld EPS = 1e-9;

void add_have(ld x) {
	for (auto &i : have) if (abs(i - x) < EPS) return;
		have.push_back(x);
}

ld pows(ld a, ld b) {
	return pow(a, b);
}

int stupid(int a, int b) {
	have.clear();
	add_have(a + b);
	add_have(a * b);
	add_have(a - b);
	add_have(b - a);
	if (a != 0)
		add_have((ld) b / a);
	if (b != 0)
		add_have((ld) a / b);
	if (a != 0 || (a == 0 && b > 0))
		add_have(pows(a, b));
	if (b != 0 || (b == 0 && a > 0))
		add_have(pows(b, a));
	return have.size();
}

void stress() {
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			if (smart(a, b) != stupid(a, b)) {
				cout << a << " " << b << " " << smart(a, b) << " " << stupid(a, b) << endl;
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("differ.in", "r", stdin);
	//freopen("differ.out", "w", stdout);
	//stress();
	//return 0;
	int a, b;
	cin >> a >> b;
	cout << smart(a, b) << endl;
	return 0;
}