#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 2e5 + 10;
int n;
int p[MAXN], rp[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i];
}

struct Fenvik{
	int n;
	vector<int> tree;
	Fenvik() {}
	Fenvik(int sz) {
		n = sz;
		tree.assign(n, 0);
	}
	void upd(int pos) {
		for (; pos < n; pos |= (pos + 1))
			tree[pos]++;
	}

	int Get(int pos) {
		int ans = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
			ans += tree[pos];
		return ans;
	}

	int get(int pos) {
		return Get(n - 1) - Get(pos - 1);
	}
};

int fans = 0;

int ans[MAXN];
Fenvik help;

void calc1() {
	Fenvik fenvik(n);
	for (int i = 0; i < n; i++) {
		ans[i] = fenvik.get(rp[i]);
		fenvik.upd(rp[i]);
		/*cout << "fenvik = " << endl;
		for (auto j : fenvik.tree)
			cout << j << " ";
		cout << endl;*/
	}
	/*cout << "ans = " << endl;
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;*/

	for (int i = 1; i < n; i++)
		ans[i] += ans[i - 1];
	cout << "ans = " << endl;
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;
}

set<int> pos;

int get(int l, int r, int cnt) {
	cout << "l = " << l << " r = " << r << " cnt = " << cnt << endl;
	if (r < l) return 0;
	int fans = help.Get(l);
	cout << "q = " << fans << ", " << cnt - fans <<  endl;
	cout << endl;
	return min(fans, cnt - fans) * (r - l + 1);
}

void calc2() {
	help = Fenvik(n);
	for (int i = 0; i < n; i++) {
		help.upd(rp[i]);
	
		if (pos.empty()) {
		}
		else if (*pos.begin() > rp[i]) {
			fans += get(rp[i] + 1, (*pos.begin()) - 1, i + 1);
	//		cout << endl;
		}
		else if (*(--pos.end()) < rp[i]) {
			fans += get(*(--pos.end()) + 1, rp[i] - 1, i + 1);
	//		cout << endl;
		}
		else {
			auto it = --lower_bound(all(pos), rp[i]);
			auto it2 = it;
			--it2;
			int l = *it;
			int r = *it2;
			fans -= get(l + 1, r - 1, i);
			fans += get(l + 1, rp[i] - 1, i + 1);
			fans += get(rp[i] + 1, r - 1, i + 1);
		}

		cout << "fans = " << fans << endl;
		ans[i] += fans;
		pos.insert(rp[i]);
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		p[i]--;
		rp[p[i]] = i;
	}
	/*cout << "rp = " << endl;
	for (int i = 0; i < n; i++)
		cout << rp[i] << " ";
	cout << endl;*/
	calc1();
	calc2();
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
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