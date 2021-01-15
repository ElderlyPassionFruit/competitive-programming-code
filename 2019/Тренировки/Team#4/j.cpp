#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int k, n, m;
string s, t;

void read() {
	cin >> k >> s >> t;
	n = s.size();
	m = t.size();
}

map <char, int> have;
set <char> x;
int cnt = 0;
void build() {
	for (auto i : t) {
		x.insert(i);
		have[i]++;
	}
}

void add(char a) {
	if (!x.count(a)) 
		return;
	if (have[a] > 0)
		cnt++;
	have[a]--;
}

void del(char a) {
	if (!x.count(a))
		return;
	if (have[a] >= 0)
		cnt--;
	have[a]++;
}

bool get_ans() {
	return cnt == k;
}

bool ans;

void run() {
	ans = false;
	if (k > min(n, m))
		return;

	build();
	for (int i = 0; i < k - 1; i++)
		add(s[i]);
	for (int i = k - 1; i < n; i++) {
		add(s[i]);
		ans |= get_ans();
		del(s[i - k + 1]);
	}
}

void write() {
	if (ans) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
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