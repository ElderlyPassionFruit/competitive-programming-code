#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 51;
int n;
bool reg, num;
string a[N];

void read() {
	cin >> n;
	string s;
	cin >> s;
	reg = (s == "yes");
	cin >> s;
	num = (s == "yes");
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

char getNorm(char x) {
	if (x >= 'A' && x <= 'Z') {
		return x - 'A' + 'a';
	}
	return x;
}

bool checkSame(string a, string b) {
	if (a.size() != b.size()) return false;
	for (int i = 0; i < (int)a.size(); i++) {
		if (reg) {
			if (a[i] != b[i]) return false;
		} else {
			if (getNorm(a[i]) != getNorm(b[i])) return false;
		}
	}
	return true;
}

string norm(string s) {
	if (reg) return s;
	string ans = "";
	for (auto i : s) {
		ans += getNorm(i);
	}
	return ans;
}

map<string, int> cnt;
map<string, int> firstPos;

void upd(string s, int it) {
	s = norm(s);
	for (int i = 0; i < n; i++) {
		if (checkSame(s, a[i])) return;
	}
	cnt[s]++;
	if (!firstPos.count(s)) {
		firstPos[s] = it;
	}
}

bool checkChar(char x) {
	if (x >= 'a' && x <= 'z') return true;
	if (x >= 'A' && x <= 'Z') return true;
	if (x >= '0' && x <= '9') return true;
	if (x == '_') return true;
	return false;
}

bool checkString(string s) {
	if (s.empty()) return false;
	int cntNonNum = 0;
	for (auto i : s) {
		cntNonNum += !(i >= '0' && i <= '9');
	}
	if (!cntNonNum) return false;
	if (s[0] >= '0' && s[0] <= '9' && (!num)) return false;
	return true;
}

vector<string> parse(string s) {
	vector<string> ans;
	string now = "";
	for (auto i : s) {
		if (!checkChar(i)) {
			if (checkString(now)) {
				ans.push_back(now);
			}
			now = "";
		} else {
			now += i;
		}
	}
	if (checkString(now)) {
		ans.push_back(now);
	}
	return ans;
}

string ans;

void makeAns() {
	int myCnt = -1;
	int myPos = 1e9;
	for (auto i : cnt) {
		if (i.second < myCnt) continue;
		if (i.second == myCnt && myPos < firstPos[i.first]) continue;
		ans = i.first;
		myCnt = i.second;
		myPos = firstPos[ans];
	}
	assert(!ans.empty());
}

void run() {
	string s;
	int it = 0;
	while (cin >> s) {
		auto have = parse(s);
		for (auto i : have) {
			upd(i, it++);
		}
	}
	makeAns();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}