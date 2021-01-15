#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int gcd(int a, int b, int c) {
	a = abs(a);
	b = abs(b);
	c = abs(c);
	return gcd(gcd(a, b), c);
}

struct line{
	int a, b, c;
	line() {}
	line(int x, int y, int z) {
		int g = gcd(x, y, z);
		a = x / g, b = y / g, c = z / g;
		if (a < 0) {
			a *= -1, b *= -1, c *= -1;
		}
		else if (a == 0 && b < 0) {
			b *= -1, c *= -1;
		}
		else if (a == 0 && b == 0 && c < 0) {
			c *= -1;
		}
	}
};

bool operator<(const line & a, const line & b) {
	return tie(a.a, a.b, a.c) < tie(b.a, b.b, b.c); 
}

bool operator==(const line & a, const line & b) {
	return tie(a.a, a.b, a.c) == tie(b.a, b.b, b.c);
}

bool check(const line & a, const line & b) {
	return !(a == b) && (a.a * b.b == a.b * b.a);
}

int n;

void read() {
	cin >> n;
}

struct num{
	int x, y;
	num() {}
	num(int a, int b) {
		if (a == 0 && b == 0) {
			x = 0, y = 0;
		}
		else if (a == 0) {
			x = 0, y = 1;
		}
		else if (b == 0) {
			x = 1, y = 0;
		}
		else {
			int g = __gcd(a, b);
			x = a / g;
			y = b / g;
		}
	}
};

bool operator<(const num & a, const num & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

map<line, int> have;
map <num, int> cnt;
int sum = 0;

vector<pair<line, int>> x;

void add(line l, int q) {
	//x.push_back({l, q});
	have[l] += q;
	cnt[num(l.a, l.b)] += q;
	sum += q;
}

void solve(line l) {
	/*int sum1 = 0, sum2 = 0;
	for (auto i : x) {
		if (i.first == l)
			sum1 += i.second;
		else if (!check(i.first, l))
			sum2 += i.second;
	}
	if (sum1 != 0) {
		cout << "inf" << endl;
	}
	else {
		cout << sum2 << endl;
	}*/
	if (have[l] != 0) {
		cout << "inf" << "\n";
		return;
	}
	cout << sum - cnt[num(l.a, l.b)] << "\n";
}

void run() {
	for (int i = 0; i < n; i++) {
		int type;
		int a, b, c;
		cin >> type;
		cin >> a >> b >> c;
		line l(a, b, c);
		if (type == 1) {
			int q;
			cin >> q;
			add(l, q);
		}
		else {
			solve(l);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}