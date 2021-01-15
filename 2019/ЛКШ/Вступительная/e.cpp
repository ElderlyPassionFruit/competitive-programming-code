#include <bits/stdc++.h>

using namespace std;
//#define int long long
//#define double long double
struct fenvik
{
	vector <vector <double> > tree;
	int n;

	fenvik() {
		n = {};
		tree = {};
	}

	fenvik(int sz) {
		n = sz + 10;
		tree.assign(n, vector <double> (n, 0));
	}

	double sum(int x, int y) {
		double ans = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
				ans += tree[i][j];

		/*for (int i = x; i >= 0; i--) {
			for (int j = y; j >= 0; j--) {
				ans += tree[i][j];
			}
		}*/
		return ans;
	}

	double sum(int x1, int y1, int x2, int y2) {
		double ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;
		ans1 = sum(x1 - 1, y1 - 1);
		ans2 = sum(x1 - 1, y2);
		ans3 = sum(x2, y1 - 1);
		ans4 = sum(x2, y2);
		return ans4 + ans1 - ans2 - ans3;
	}

	void inc(int x, int y, double delta) {
		for (int i = x; i < n; i = (i | (i + 1)))
			for (int j = y; j < n; j = (j | (j + 1)))
				tree[i][j] += delta;
	}
};

fenvik t1, t2, t3, g1, g2;
int n, m;
const int MAXN = 1e5 + 10;
double arr[MAXN];
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

void add(int h1, int h2) {
	if (h1 > h2)
		swap(h1, h2);
	if (h1 != h2) {
		t1.inc(h2, h1, 1.0 / (h2 - h1));
		t2.inc(h2, h1, 1.0 * 2 * h1 / (h2 - h1));
		t3.inc(h2, h1, 1.0 * h1 * h1 / (h2 - h1));
	}
	g1.inc(h2, h1, 1.0 * (h1 + h2) / 2);
	g2.inc(h2, h1, 1);
}

void del(int h1, int h2) {
	if (h1 > h2)
		swap(h1, h2);
	if (h1 != h2) {
		t1.inc(h2, h1, -1.0 / (h2 - h1));
		t2.inc(h2, h1, -1.0 * 2 * h1 / (h2 - h1));
		t3.inc(h2, h1, -1.0 * h1 * h1 / (h2 - h1));
	}
	g1.inc(h2, h1, -1.0 * (h1 + h2) / 2);
	g2.inc(h2, h1, -1);
}

double get_ans(int h) {
	double ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0, ans5 = 0;
	ans1 = t1.sum(h + 1, 0, 1001, h - 1);
	ans2 = t2.sum(h + 1, 0, 1001, h - 1);
	ans3 = t3.sum(h + 1, 0, 1001, h - 1);
	ans4 = g1.sum(0, 0, h, h);
	ans5 = g2.sum(0, 0, h, h);
	return (ans1 * h * h - ans2 * h + ans3) / 2 + ans5 * h - ans4;
}

vector <double> ans;

void run() {
	t1 = fenvik(1010);
	t2 = fenvik(1010);
	t3 = fenvik(1010);
	g1 = fenvik(1010);
	g2 = fenvik(1010);

	for (int i = 1; i < n; i++) {
		add(arr[i], arr[i - 1]);
	}

	for (int test = 0; test < m; test++) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int h;
			cin >> h;
			double fans = get_ans(h);
			ans.push_back(fans);
		}
		else {
			int pos, val;
			cin >> pos >> val;
			if (pos != 0)
				del(arr[pos], arr[pos - 1]);
			if (pos != n - 1)
				del(arr[pos], arr[pos + 1]);
			arr[pos] = val;
			if (pos != 0)
				add(arr[pos], arr[pos - 1]);
			if (pos != n - 1)
				add(arr[pos], arr[pos + 1]);
		
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << endl;
}

signed main() {
	cout.precision(6);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}