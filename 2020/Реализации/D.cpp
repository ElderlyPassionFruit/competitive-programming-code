#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int INF = -1e9;
pair<int, int> ans_first = {INF, INF}, ans_second = {INF, INF};

bool is_num(char x) {
	return x >= '0' && x <= '9';
}

bool is_int(string & s) {
	if (s.empty()) return false;
	for (auto i : s) {
		if (!is_num(i))
			return false;
	}
	return true;
}

bool is_randseed(string s) {
	int cnt = 0;
	string t = "";
	s += " ";
	for (auto i : s) {
		if (i == ' ') {
			if (cnt == 0) {
				//cout << t << endl;
				if (t != "randseed") return false;
			}
			else if (cnt == 1) {
				//cout << t << endl;
				if (t != "=") return false;
			}
			else if (cnt == 2) {
				//cout << t << endl;
				if (!is_int(t) || (t.size() > 9 && t != "1000000000")) return false;
			}
			else {
				return false;
			}
			t = "";
			cnt++;
		}
		else {
			t += i;
		}
	}
	return true;
}

int get_randseed(string & s) {
	string t = "";
	while (s.back() != ' ') {
		t += s.back();
		s.pop_back();
	}
	int ans = 0;
	while (!t.empty()) {
		ans *= 10;
		ans += t.back() - '0';
		t.pop_back();
	}
	return ans;
}

bool is_time(string s) {
	int cnt = 0;
	int cnt2 = 0;
	string t = "";
	s += " ";
	for (auto i : s) {
		if (i == ' ') {
			if (cnt == 0) {
				if (t != "Work") return false;
			}
			else if (cnt == 1) {
				if (t != "time:") return false;
			}
			else if (cnt == 2) {
				if (!is_int(t)) return false;
			}
			else if (cnt == 3) {
				if (t != "ms") return false;
			}
			else if (cnt > 3) {
				return false;
			}
			t = "";
			cnt++;
		}
		else if (i == ',') {
			if (cnt2 == 0) {
				if (!is_int(t) || (t.size() > 6 && t != "1000000")) return false;
			}
			else {
				return false;
			}
			t = "";
			cnt2++;
		}
		else {
			t += i;
		}
	}
	return true;
}

int get_time(string & s) {
	string ans = "";
	for (auto i : s) {
		if (i == ',') break;
		if (i == ' ' && !ans.empty()) break;
		if (is_num(i)) ans += i; 
	}
	//cout << ans << endl;
	int fans = 0;
	for (auto i : ans) {
		fans *= 10;
		fans += i - '0';
	}
	return fans;
}

void solve(vector<string> & a) {
	int n = a.size();
	int cnt = 0;
	int RND = -1, first = -1, second = -1;
	for (int i = 0; i < n; i++) {
		//cout << a[i] << endl; 
		//cout << is_randseed(a[i]) << endl;
		//continue;
		if (cnt == 0) {
			if (is_randseed(a[i])) {
				cnt++;
				RND = get_randseed(a[i]);
				continue;
			}
		}
		else if (cnt == 1) {
			//cout << "puhh" << endl;
			if (is_time(a[i])) {
				cnt++;
				first = get_time(a[i]);
				continue;
			}
			//cout << "puhh" << endl;
		}
		else if (cnt == 2) {
			if (is_time(a[i])) {
				cnt++;
				second = get_time(a[i]);
				continue;
			}
		}
	}
	cout << "At randseed = " << RND << endl;
	cout << "First: " << first << " ms" << endl;
	cout << "Second: " << second << " ms" << endl;
	if (ans_first.first < first) {
		ans_first = {first, RND};	
	}
	if (ans_second.first < second) {
		ans_second = {second, RND};	
	}
	//chkmax(ans_first, make_pair(first, RND));
	//chkmax(ans_second, make_pair(second, RND));
}

bool is_underline(string & s) {
	for (auto i : s) 
		if (i != '-')
			return false;
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen("stress.in", "r", stdin);
	//freopen("stress.out", "w", stdout);
	vector<string> a;
	string s;
	while (getline(cin, s)) {
		if (is_underline(s)) {
			if (a.empty()) continue;
			solve(a);
			a.clear();
		}
		else {
			a.push_back(s);
		}
	}
	cout << "Maximal work time for first: " << ans_first.first << " at randseed = " << ans_first.second << endl;
	cout << "Maximal work time for second: " << ans_second.first << " at randseed = " << ans_second.second;
	return 0;
}