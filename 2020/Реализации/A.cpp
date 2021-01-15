#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<string> monthes = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
"Nov", "Dec"};

vector<int> cnt = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_month(string s) {
	for (int i = 0; i < 12; i++)
		if (monthes[i] == s) return i;
	assert(false);
	return -1;
}

int get_int(string s) {
	bool minus = false;
	if (s[0] == '-') {
		minus = true;
		s.erase(s.begin());	
	}
	else if (s[0] == '+') {
		s.erase(s.begin());
	}
	int ans = 0;
	for (auto i : s){
		ans *= 10;
		ans += i - '0';
	}
	if (minus) ans *= -1;
	return ans;
}

pair<int, int> get_d(string now, string need) {
	pair<int, int> ans;
	string s, t;
	s = "";
	s += now[0];
	s += now[1];
	s += now[2];
	t = "";
	t += need[0];
	t += need[1];
	t += need[2];
	ans.first = get_int(s) - get_int(t);
	s = "";
	s += now[0];
	s += now[3];
	s += now[4];
	t = "";
	t += need[0];
	t += need[3];
	t += need[4];
	ans.second = get_int(s) - get_int(t);
	return ans;
}	

void make(int & minutes, int & h, int & d, int & month, int & year) {
	//int x = h + day + month + year;
	//return x;
	while (minutes >= 60) {
		minutes -= 60;
		h++;
	}
	while (minutes < 0) {
		minutes += 60;
		h--;
	}
	while (h >= 24) {
		h -= 24;
		d++;
	}
	while (h < 0) {
		h += 24;
		d--;
	}
	//assert(d >= 0);
	if (d <= 0) {
		month--;
		if (month < 0) {
			month = 11;
			year--;
		}
		d = cnt[month] + d;
		if (month == 1 && year % 4 == 0)
			d++;
	}
	//assert(d <= cnt[month] + 1 + (year % 4 == 0 && month == 1));
	if (d >= cnt[month] + 1 + (year % 4 == 0 && month == 1)) {
		d -= cnt[month] + (year % 4 == 0 && month == 1) ;
		month++;
		if (month == 12) {
			month = 0;
			year++;
		}
	}
}

string get(int num) {
	string s = "";
	while (num) {
		s += '0' + num % 10;
		num /= 10;
	}
	while (s.size() < 2)
		s += "0";
	reverse(all(s));
	return s;
}

string make(string s, string need_time) {
	string t = "";
	t += s[1];
	t += s[2];
	int day = get_int(t);
	t = "";
	t += s[4];
	t += s[5];
	t += s[6];
	int month = get_month(t);
	t = "";
	t += s[8];
	t += s[9];
	t += s[10];
	t += s[11];
	int year = get_int(t);
	t = "";
	t += s[13];
	t += s[14];
	int h = get_int(t);
	t = "";
	t += s[16];
	t += s[17];
	int m = get_int(t);
	string fans = "";
	fans += s[18];
	fans += s[19];
	fans += s[20];

	t = "";
	t += s[22];
	t += s[23];
	t += s[24];
	t += s[25];
	t += s[26];
	pair<int, int> diff = get_d(t, need_time);
	h -= diff.first;
	m -= diff.second;
	make(m, h, day, month, year);
	return "[" + get(day) + "/" + monthes[month] + "/" + get(year) + ":" + get(h) + ":" + get(m) + fans + " " + need_time + "]"; 
}

string solve(string s, string need_time) {
	int cnt = 0;
	string t1 = "", t2 = "", t3 = "";
	for (auto i : s) {
		if (i == ' ') {
			cnt++;
			if (cnt == 3 || cnt == 5) continue;
		}
		if (cnt < 3)
			t1 += i;
		else if (cnt < 5)
			t2 += i;
		else 
			t3 += i;
	}
//	cout << t1 << "\n" << t2 << "\n" << t3 << endl;
	return t1 + " " + make(t2, need_time) + " " + t3;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("apache.in", "r", stdin);
	freopen("apache.out", "w", stdout);
	string my_time;
	getline(cin, my_time);
	string s;
	while (getline(cin, s)) {
//		cout << s << endl;
		cout << solve(s, my_time) << endl;
	}
	return 0;
}