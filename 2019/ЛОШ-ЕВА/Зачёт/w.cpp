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

const int MAXN = 5e5 + 10;

pair <int, int> ans;

int pos[MAXN];
int ind[MAXN];
int last_one[MAXN];
int last_zero[MAXN];

void calc() {
	int cnt = 1;
	for (int i = 1; i <= n; i++) {
		if (s[i - 1] == '0') 
			pos[cnt++] = i;
	}

	cnt = 1;
	for (int i = 1; i <= n; i++) {
		if (s[i - 1] == '0')
			ind[i] = cnt++;
	}

	last_one[n] = n + 1;
	for (int i = n; i >= 0; i--) {
		last_one[i] = last_one[i + 1];
		if (s[i - 1] == '1')
			last_one[i] = i;
	}

	last_zero[n] = n + 1;
	for (int i = n; i >= 0; i--) {
		last_zero[i] = last_zero[i + 1];
		if (s[i - 1] == '0')
			last_zero[i] = i;
	}
}

int get_len(int cnt) {
	int len = 0;
	int p = last_zero[0];
	while (p <= n) {
		if (p + cnt - 1 > n || ind[p] + cnt - 1 > n || pos[ind[p] + cnt - 1] == 0) return len - 1;
		len += cnt + 1;
		p = pos[ind[p] + cnt - 1];
		if (last_one[p] == 0) break;
		p = last_one[p];
		if (last_zero[p] == 0) break;
		p = last_zero[p];
	}
	return len - 1;
}

void run() {
	calc();
	ans = {0LL, 0LL};
	for (int i = 0; i < n; i++){
		if (s[i] == '1')
			ans.first++;	
	}
	for (int i = 1; i <= n; i++) {
		int x = get_len(i);
		if (x != i)
			ans = max(ans, {x, i});
	}
}

string gen(pair <int, int> ans) {
	string a = "";
	int len = ans.first;
	int z = ans.second;
	for (int i = 1; i <= len; i++) {
		if (i % (z + 1) == 0)
			a += "1";
		else
			a += "0";
	} 
	return a;
}

void write() {
	auto x = gen(ans);
	cout << x.size() << endl;
	cout << x << endl;
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