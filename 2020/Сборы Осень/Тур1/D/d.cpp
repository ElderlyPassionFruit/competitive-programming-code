#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
unordered_map<string, int> s00, s01, s10, s11;

int p;

struct event{
	string l, r;
	bool f1, f2;
	event() {
		l = "";
		r = "";
		f1 = false;
		f2 = false;
	}
};

void make(string & s) {
	if (s[0] == '*') {
		reverse(all(s));
		s.pop_back();
		s.pop_back();
		reverse(all(s));
	}
	if (s.back() == '*') {
		s.pop_back();
		s.pop_back();
	}
}

event get(string & s) {
	event ans = event();
	if (s[0] == '*') {
		ans.f1 = true;
	}
	if (s.back() == '*') {
		ans.f2 = true;
	}
	make(s);
	bool flag = false;
	for (auto i : s) {
		if (i == '/')
			flag = true;
		if (!flag)
			ans.l += i;
		else
			ans.r += i;
	}
	return ans;
}

void add(string & s) {
	auto x = get(s);
	if (x.f1 && x.f2) {
		s11[s]++;
	}
	else if (x.f1 && !x.f2) {
		s10[s]++;
	}
	else if (x.f2 && !x.f1) {
		s01[s]++;
	}
	else if (!x.f1 && !x.f2) {
		s00[s]++;
	}
}

void read() {
	cin >> n >> p;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add(s);
	}	
}

vector<string> genl(string & s) {
	vector<string> ans;
	reverse(all(s));

	string now = "";
	for (auto i : s) {
		if (i == '.')
			ans.push_back(now);
		now += i;
	}

	ans.push_back(now);

	reverse(all(s));
	for (auto &i : ans) {
		reverse(all(i));
	}

	return ans;
}

vector<string> genr(string & s) {
	vector<string> ans;
	string now = "";
	for (auto i : s) {
		if (i == '/')
			ans.push_back(now);
		now += i;
	}
	ans.push_back(now);
	return ans;
}

int get00(event & a) {
	return s00[a.l + a.r];
}

int get01(event & a, vector<string> & y) {
	int ans = 0;
	for (auto i : y) {
		if (s01.find(a.l + i) != s01.end())
			ans += s01[a.l + i];
	}
	return ans;
}

int get10(event & a, vector<string> & x) {
	int ans = 0;
	for (auto i : x) {
		if (s10.find(i + a.r) != s10.end())
			ans += s10[i + a.r];
	}
	return ans;
}

int get11(vector<string> & x, vector<string> & y) {
	int ans = 0;
	for (auto i : x) {
		for (auto j : y) {
			if (s11.find(i + j) != s11.end())
				ans += s11[i + j];
		}
	}
	return ans;
}

vector<int> ans;

void run() {
	cin >> k;
	for (int i = 0; i < k; i++) {
		string s;
		cin >> s;
		auto a = get(s);
		auto x = genl(a.l);
		auto y = genr(a.r);

		int fans = 0;
		
		fans += get00(a);
		fans += get01(a, y);
		fans += get10(a, x);
		fans += get11(x, y);
		
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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