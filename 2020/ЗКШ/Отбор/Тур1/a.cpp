#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int a, b;

void read() {
	cin >> a >> b;
}

bool check(int cnt, int a, int b) {
	for (int i = 0; i < cnt; i++) {
		if (a >= cnt - i) {
			a -= cnt - i;
		}
		else {
			b -= cnt - i;
		}
	}
	return a >= 0 && b >= 0;
}

bool check(int cnt) {
	return check(cnt, a, b) || check(cnt, b, a);
}

vector<string> gen_ans(int cnt) {
	char w = 'W', r = 'R';
	if (!check(cnt, a, b))
		swap(a, b), swap(w, r);
	assert(check(cnt, a, b));
	vector<string> ans;
	ans.resize(cnt, "");
	if (b >= cnt){
		b -= cnt;
		ans[0] = r;
	}
	else {
		a -= cnt;
		ans[0] = w;
	}
	for (int i = 1; i < cnt; i++) {
		ans[i] = ans[i - 1];
		if (b >= cnt - i){
			b -= cnt - i;
			ans[i] += r;
		}
		else {
			a -= cnt - i;
			ans[i] += w;
		}
	}
	return ans;
}

void run() {
	int l = 0, r = a + b + 10;
	//cout << check(3, 5, 5) << endl;
	//return;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	auto ans = gen_ans(l);
	cout << l << "\n";
	for (auto i : ans)
		cout << i << "\n"; 
}

void write() {

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