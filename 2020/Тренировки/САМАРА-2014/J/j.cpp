#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()


mt19937 rnd(time(0));
int now = 0;
vector<int> s;
int my_op = 0;
bool TEST = false;	

void gen_test() {
	int len = rnd() % 1 + 1;
	for (int i = 0; i < len; i++) {
		s.push_back(rnd() % 2);
	}
}

int last_val;

int query(char x) {
	if (TEST) {
		cerr << x << endl;
		my_op++;
		assert(my_op <= 10 * s.size());
		if (x == 'L') {
			now--;
			if (now < 0) now = s.size() - 1;
		} else if (x == 'R') {
			now++;
			if (now == s.size()) now = 0;
		} else {
			s[now] ^= 1;
		}
		cerr << "now = " << now << " s = ";
		for (auto i : s) cerr << i << " ";
		cerr << endl;
		return s[now];
	} else {
		cout << x << endl;
		if (x == 'S') last_val ^= 1;
		else cin >> last_val;
		return last_val;
	}
}

void out_ans(int x) {
	cout << x << endl;
	if (TEST) {
		assert(x == s.size());
	}
	exit(0);
}

const int BUBEN = 30;
int L, pos, val_now, start_val;
int mx_pos;
int op = 0;

void nxt() {
	val_now = query('L');
	if (val_now == start_val) {
		query('S');
	}
	pos++;
	mx_pos = max(pos, mx_pos);
	op++;
}

bool check() {
	return L * 10 - op - 2 - pos - 1 - pos >= 0;
}

void go_back() {
	while (pos > 0) {
		val_now = query('R');
		pos--;
		op++;
	}
}

vector<int> gen() {
	vector<int> ans;
	for (int i = 0; i < BUBEN; i++) {
		ans.push_back((rnd() % 2 + 2) % 2);
		int have = query('L');
		if (have != ans.back()) {
			query('S');
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//out_ans(1);

	if (TEST) {
		gen_test();
		start_val = s[0];
	} else {
		cin >> start_val;
		last_val = start_val;
	}
	L = 1;
	while (L < BUBEN) {
		while (check() && pos < BUBEN) {
			nxt();
		}
		go_back();
		if (val_now == start_val) {
			L = mx_pos + 1;
			continue;
		}
		int need = query('S');
		int ans = 1;
		while (query('L') != need) {
			ans++;
		}
		out_ans(ans);
	}
	auto need = gen();
	vector<int> have;
	int ans = 0;
	while (have != need) {
		ans++;
		int now = query('L');
		have.push_back(now);
		if (have.size() > BUBEN) {
			have.erase(have.begin());
		}
	}
	out_ans(ans);
	return 0;
}