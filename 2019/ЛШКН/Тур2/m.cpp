#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string s;
void read() {
	cin >> n >> s;
}

int ans;

void run() {
	map <char, char> op;
	op['L'] = 'R';
	op['R'] = 'L';
	op['U'] = 'D';
	op['D'] = 'U';

	ans = 1;
	if (s.size() <= 2)
		return;
	vector<char> st;
	st.push_back(s[0]);
	for (int i = 1; i < n; i++) {
		if (st.size() < 2) {
			if (st.back() != s[i] && st.back() != op[s[i]])
				st.push_back(s[i]);
			else if (st.back() == op[s[i]]) {
				st.clear();
				st.push_back(s[i]);
				ans++;
			}
		}
		else {
			if (st[st.size() - 1] != s[i] && st[st.size() - 2] != s[i]) {
				ans++;
				st.clear();
				st.push_back(s[i]);
			}
		}
	}
}

void write() {
	cout << ans << endl;
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