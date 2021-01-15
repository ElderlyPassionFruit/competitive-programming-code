#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct segment{
	int len, num;
	segment() {}
	segment(int _len, int _num) {
		len = _len;
		num = _num;
	}
};

struct lnum{
	vector<segment> have;
	vector<int> pref;
	lnum() {}
	lnum(vector<segment> _have) {
		have = _have;
		for (auto i : have)
			pref.push_back(i.len);
		for (int i = 1; i < pref.size(); i++)
			pref[i] += pref[i - 1];
	}
};

lnum operator+(lnum a, lnum b) {
	int cnt = a.pref.back() - b.pref.back();
	if (cnt > 0) {
		b.have.push_back({cnt, 0});
		b.pref.push_back(a.pref.back());
	}
	else if (cnt < 0) {
		a.have.push_back({-cnt, 0});
		a.pref.push_back(b.pref.back());
	}
	a.have.push_back({1, 0});
	b.have.push_back({1, 0});
	a.pref.push_back(a.pref.back() + 1);
	b.pref.push_back(b.pref.back() + 1);
	/*cout << "a.have = " << endl;
	for (auto i : a.have)
		cout << i.len << " " << i.num << endl;
	cout << endl;
	cout << "b.have = " << endl;
	for (auto i : b.have)
		cout << i.len << " " << i.num << endl;
	cout << endl;*/

	int pos = 0;
	vector<segment> haveA, haveB;
	
	for (int i = 0; i < a.have.size(); i++) {
		int len = a.have[i].len;
		while (pos < b.have.size() && len) {
			int flen = min(len, b.have[pos].len);
			haveA.push_back({flen, a.have[i].num});
			haveB.push_back({flen, b.have[pos].num});
			b.have[pos].len -= flen;
			len -= flen;
			if (b.have[pos].len == 0)
				pos++;
		}
	}	
	assert(haveA.size() == haveB.size());
	
	/*cout << "haveA = " << endl;
	for (auto i : haveA)
		cout << i.len << " " << i.num << endl;
	cout << endl;
	cout << "haveB = " << endl;
	for (auto i : haveB)
		cout << i.len << " " << i.num << endl;
	cout << endl;*/

	vector<segment> ans;
	reverse(all(haveA));
	reverse(all(haveB));

	int add = 0;
	
	while (!haveA.empty()) {
		auto a = haveA.back();
		auto b = haveB.back();
		haveA.pop_back();
		haveB.pop_back();
		if (a.num + b.num + add >= 10 ) {
			if (add == 0) {
				ans.push_back({1, (a.num + b.num) % 10});
				ans.push_back({a.len - 1, (a.num + b.num + 1) % 10});
				add = 1;
			}
			else {
				ans.push_back({a.len, (a.num + b.num + 1) % 10});
				add = 1;	
			}
		}
		else {
			ans.push_back({1, a.num + b.num + add});
			ans.push_back({a.len - 1, a.num + b.num});
			add = 0;
		}
	}
	/*for (auto i : ans)
		cout << i.len << " " << i.num << endl;*/
	return lnum(ans);
}

lnum readLnum() {
	string s;
	cin >> s;
	vector<segment> have;
	int cnt = 0;
	int last = 0;
	bool flag1 = false, flag2 = false;
	for (auto i : s) {
		if (i == '[') {
			cnt = 0;
			flag1 = true;
		}
		else if (i == ']') {
			flag1 = false;
			flag2 = true;
		}
		else if (flag1) {
			cnt *= 10;
			cnt += i - '0';
		}
		else if (flag2) {
			last = i - '0';
			have.push_back({cnt, last});
			flag2 = false;
		}
		else {
			cnt = 1;
			last = i - '0';
			have.push_back({cnt, last});
		}
	}
	reverse(all(have));
	/*cout << "have = " << endl;
	for (auto i : have)
		cout << i.len <<  " " << i.num << endl;
	cout << endl;*/
	return lnum(have);
}

lnum a, b, sum;

void read() {
	a = readLnum();
	b = readLnum();
	sum = a + b;
}

int solve(int pos) {
	pos = upper_bound(all(sum.pref), pos) - sum.pref.begin();
	if (pos == sum.pref.size()) return 0;
	return sum.have[pos].num;
}

vector<int> ans;

void run() {
	int t;
	cin >> t;
	while(t--) {
		int pos;
		cin >> pos;
		//cout << solve(pos) << "\n";
		ans.push_back(solve(pos));
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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