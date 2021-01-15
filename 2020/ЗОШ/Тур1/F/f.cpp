#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e5 + 10;
ll l, a, b, T, R;
int n;
ll x[MAXN];

void read() {
	cin >> l >> a >> b >> T >> R;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	x[n + 1] = l;
}

ld dp[MAXN];
int p[MAXN];

vector<int> ans;

struct fset{
	ld fans;
	int pos;
	fset() {}
	fset(ld a, int b) {
		fans = a, pos = b;
	}
};

bool operator<(const fset & a, const fset & b) {
	return tie(a.fans, a.pos) < tie(b.fans, b.pos);
}

const ld INF = 1e18 + 10;

struct Stack{
	vector<fset> st;
	vector<fset> mx;
	void push(fset x) {
		st.push_back(x);
		if (mx.empty())
			mx.push_back(x);
		else
			mx.push_back(min(mx.back(), x));
	}
	void pop() {
		st.pop_back();
		mx.pop_back();
	}
	fset get_element() {
		if (!st.empty())
			return st.back();
		return {INF, -1};
	}
	fset get_ans() {
		if (!st.empty())
			return mx.back();
		return {INF, -1};
	}
};

struct Queue{
	Stack top, end;
	void rebuild() {
		while (!top.st.empty()) {
			end.push(top.get_element());
			top.pop();
		}
	}
	void push(fset x) {
		top.push(x);
	}
	void pop() {
		if (end.st.empty()) rebuild();
		end.pop();
	}
	fset get() {
		return min(top.get_ans(), end.get_ans());
	}
	bool empty() {
		return top.st.empty() && end.st.empty();
	}
};

void run() {
	Queue have;
	fset now = {INF, -1};
	int l = n + 1, r = n + 1;
	for (int i = n; i >= 1; i--) {
		dp[i] = dp[i + 1] + (ld)(x[i + 1] - x[i]) / a;
		p[i] = p[i + 1];
		while (l > i && x[l] - x[i] > a * T) {
			have.push({(dp[l] + T + (ld)(x[l] - a * T) / b), l});
			l--;
		}
		while (r > l && x[r] - x[i] > a * T + b * R) {
			have.pop();
			chkmin(now, fset((dp[r] + R + (ld) (x[r] - b * R) / a), r));
			r--;
		}
		if (now.fans != INF) {
			ld fans = now.fans -(ld)x[i] / a;
			if (fans < dp[i]) {
				dp[i] = fans;
				p[i] = now.pos;
			}		
		}
		if (!have.empty()) {
			auto now = have.get();
			ld fans = now.fans - (ld)x[i] / b;
			if (fans < dp[i]) {
				dp[i] = fans;
				p[i] = now.pos;
			}
		}
	}

	p[0] = 1;
	int pos = 0;
	while (p[pos] != n + 1 && p[pos] != 0) {
		ans.push_back(p[pos]);
		pos = p[pos];
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i - 1 << " ";
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