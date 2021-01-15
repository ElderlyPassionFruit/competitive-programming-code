#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct tree{
	int n, sum_height, ans;
	string s;
	tree() {}
	tree(int _n, int _sum_height, int _ans, string _s) {
		n = _n, sum_height = _sum_height, ans = _ans, s = _s;
	}
};

const int MAXN = 21, MAXH = 201, MAXANS = 2001;

bool used[MAXN][MAXH][MAXANS];
vector<tree> trees[MAXN];

void relax(tree have) {
	if (used[have.n][have.sum_height][have.ans]) return;
	used[have.n][have.sum_height][have.ans] = true;
	trees[have.n].push_back(have);
}

void no() {
	cout << "NO\n";
	exit(0);
}

void make_ans(string s) {
	cout << "YES\n";
	vector<int> st;
	st.push_back(1);
	int last = 1;
	for (auto x : s) {
		if (x == '(') {
			last++;
			cout << st.back() << " " << last << "\n";
			st.push_back(last); 
		} else {
			st.pop_back();
		}
	}
	exit(0);
}

void wr(tree nxt) {
	cout << "n = " << nxt.n << " sum_height = " << nxt.sum_height << " ans = " << nxt.ans << " tree = " << nxt.s << endl; 		
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	if (m >= MAXANS) {
		no();
	}

	trees[1].push_back({1, 0, 0, ""});

	for (int cnt = 2; cnt <= n; cnt++) {
		for (auto old : trees[cnt - 1]) {
			tree nxt = tree(cnt, old.sum_height + (cnt - 1), old.ans + old.sum_height + (cnt - 1), "(" + old.s + ")");
			relax(nxt);
		}
		for (int l = 1; l < cnt; l++) {
			int r = cnt - l;
			for (auto L : trees[l]) {
				for (auto R : trees[r]) {
					//cout << "L = " << endl;
					//wr(L);
					//cout << "R = " << endl;
					//wr(R);

					tree nxt = tree(
						cnt,
						L.sum_height + R.sum_height + R.n,
						L.ans + R.ans + L.n * (R.sum_height + R.n) + R.n * L.sum_height,
						L.s + "(" + R.s + ")"
						);
					//cout << "nxt = " << endl;
					//wr(nxt);

					relax(nxt);
				}
			}
		}
	}

	for (auto have : trees[n]) {
		if (have.ans == m) {
			make_ans(have.s);
		} 
	}

	no();
	return 0;
}