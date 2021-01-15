#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

typedef vector<int> lnum;

lnum read() {
	string s;
	cin >> s;
	lnum ans(s.size());
	for (int i = 0; i < s.size(); i++)
		ans[i] = s[i] - '0';
	reverse(all(ans));
	return ans;
}

bool operator<(const lnum & a, const lnum & b) {
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = a.size() - 1; i >= 0; i--)
		if (a[i] != b[i])
			return a[i] < b[i];
	return false;
}

lnum operator-(lnum a, lnum b) {
	assert(!(a < b));
	int n = a.size();
	while (b.size() < n)
		b.push_back(0);
	for (int i = 0; i < n; i++) {
		a[i] -= b[i];
		if (a[i] < 0) {
			a[i] += 10;
			assert(i + 1 < n);
			a[i + 1]--;
		}
	}
	while (!a.empty() && a.back() == 0)
		a.pop_back();
	return a;
}

lnum operator*(lnum a, int b) {
	a.push_back(0);
	int n = a.size();
	for (int i = 0; i < n; i++) {
		a[i] *= b;
	}
	for (int i = 0; i < n; i++) {
		if (a[i] >= 10) {
			assert(i + 1 < n);
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	while (!a.empty() && a.back() == 0)
		a.pop_back();
	return a;
}

lnum operator+(lnum a, lnum b) {
	int n = max(a.size(), b.size()) + 1;
	while (a.size() < n) a.push_back(0);
	while (b.size() < n) b.push_back(0);
	for (int i = 0; i < n; i++) {
		a[i] += b[i];
		if (a[i] >= 10) {
			assert(i + 1 < n);
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	while (!a.empty() && a.back() == 0)
		a.pop_back();
	return a;
}

struct event{
	lnum up, down, fans;
	int zeroes;
};

void wr(lnum x) {
	reverse(all(x));
	for (auto i : x)
		cout << i;
}


event div(lnum & a, lnum b) {
	lnum c = b;
	int cnt = 0;
	reverse(all(c));
	while(c.size() < a.size()){
		c.push_back(0);
		cnt++;
	}
	reverse(all(c));
	if (a < c) {
		reverse(all(c));
		c.pop_back();
		cnt--;
		reverse(all(c));
	}
	int x = 0;

	for (int i = 1; i < 10; i++) {
		if (!(a < (c * i))) {	
			x = i;
		}
	}
	
	c = c * x;
	event ans = {a, c, {x}, cnt};
	reverse(all(ans.up));
	reverse(all(ans.down));
	reverse(all(ans.fans));
	for (int i = 0; i < cnt; i++) {
		ans.up.pop_back();
		ans.down.pop_back();
		ans.fans.push_back(0);
	}
	reverse(all(ans.up));
	reverse(all(ans.down));
	reverse(all(ans.fans));
	
	a = a - c;
	return ans;
}

vector<event> get(lnum &a, lnum b) {
	vector<event> ans;
	while (!(a < b)) {
		ans.push_back(div(a, b));
	}
	return ans;
}

void check(lnum & a) {
	if (a.empty())
		a = {0};
}

bool check_num(char x) {
	return x >= '0' && x <= '9';
}

string get_underline(string a, string b, bool flag) {
	string ans = "";
	while (ans.size() < a.size())
		ans += " ";
	int pos1 = 0;
	while (pos1 < a.size() && !check_num(a[pos1]) && !check_num(b[pos1]))
		pos1++;
	int pos2 = a.size() - 1;
	while (pos2 >= 0 && !check_num(a[pos2]) && !check_num(b[pos2]))
		pos2--;
	if (flag) pos2 = a.size() - 1;
	for (int i = pos1; i <= pos2; i++)
		ans[i] = '-';
	return ans;
}

void out_ans(vector<event> ans, lnum last, lnum a, lnum b) {
	check(a), check(b), check(last);
	for (auto &i : ans)
		check(i.up), check(i.down), check(i.fans);
	lnum fans = {};
	for (auto i : ans)
		fans = fans + i.fans;
	check(fans);

	vector<string> fout;
	for (auto i : ans) {
		string f1 = "";
		for (int j = 0; j < i.zeroes; j++)
			f1 += " ";
		for (auto j : i.up)
			f1 += '0' + j;
		while (f1.size() < a.size())
			f1 += " ";
		fout.push_back(f1);
		f1 = "";
		for (int j = 0; j < i.zeroes; j++)
			f1 += " ";
		for (auto j : i.down)
			f1 += '0' + j;
		while (f1.size() < a.size())
			f1 += " ";
		fout.push_back(f1);
	}
	if (fout.size()) {
		for (int i = 0; i < a.size(); i++)
			fout[0][i] = '0' + a[i];
		string f1 = "";
		for (auto i : last)
			f1 += '0' + i;
		while (f1.size() < a.size())
			f1 += " ";
		fout.push_back(f1);
	}
	else {
		string f1 = "";
		for (int i = 0; i < a.size(); i++)
			f1 += '0' + a[i];
		fout.push_back(f1);
	}
	
	vector<string> help;
	for (int i = 0; i < (int)fout.size(); i++) {
		help.push_back(fout[i]);
		if (i % 2 == 1 && i + 1 < fout.size())
			help.push_back(get_underline((i == 1 ? fout[i] : fout[i - 1]), fout[i + 1], i == 1));
	}

	fout = help;
	while (fout.size() < 3) {
		string f1 = "";
		while (f1.size() < a.size())
			f1 += " ";
		fout.push_back(f1);
	}

	int len = fout[0].size() + 2 + max(b.size(), fans.size());

	for (int i = 0; i < max((int) fout.size(), 3); i++) {
		reverse(all(fout[i]));
		if (i > 2) {
			while (fout[i].back() == ' ')
				fout[i].pop_back();
		}
		cout << fout[i];
		if (i < 3) cout << " ";
		if (i == 0) {
			cout << "|";
			wr(b);
		}
		else if (i == 1) {
			cout << "+";
			for (int j = 0; j < (int)max(b.size(), fans.size()); j++)
				cout << "-";
		}
		else if (i == 2) {
			cout << "|";
			wr(fans);
		}
		cout << "\n";	
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
	lnum a, b;
	a = read();
	b = read();
	lnum c = a;
	auto x = get(a, b);
	out_ans(x, a, c, b);
	return 0;
}