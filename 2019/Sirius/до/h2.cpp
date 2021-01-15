#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e6 + 10;
int arr[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

int tree[MAXN * 4];
int L[MAXN], R[MAXN];

void build(int v, int l, int r) {
	if (l == r - 1) {
		tree[v] = R[l];
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}

int get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l)
		return -1e9;
	if (tl >= l && tr <= r)
		return tree[v];
	int tm = (tl + tr) / 2;
	return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}

int get(int l, int r) {
	return get(1, 0, n, l, r + 1);
	/*int ans = 0;
	for (int i = l; i <= r; i++)
		ans = max(ans, R[i]);
	for (int i = l; i <= r; i++) {
		if (i - L[i] + 1 >= l) {
			ans = max(ans, L[i]);
		}
		else {
			ans = max(ans, i - l + 1);
		}
	}
	return ans;*/
}

vector <int> ans;
void run() {
	map <int, int> used;
	for (int i = 0; i < n; i++)
		used[arr[i]] = 1e9;
	for (int i = n - 1; i >= 0; i--) {
		R[i] = min(R[i + 1] + 1, used[arr[i]] - i);
		used[arr[i]] = i;
	}

	for (int i = 0; i < n; i++) {
		used[arr[i]] = -1e9;
	}

	L[0] = 1;
	used[arr[0]] = 0;
	for (int i = 1; i < n; i++) {
		L[i] = min(L[i - 1] + 1, i - used[arr[i]]);
		used[arr[i]] = i;
	}

	/*cout << "L = " << endl;
	for (int i = 0; i < n; i++)
		cout << L[i] << " ";
	cout << endl;
	cout << "R = " << endl;
	for (int i = 0; i < n; i++)
		cout << R[i] << " ";
	cout << endl; */

	build(1, 0, n);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		int mx_ans = r - l + 1;
		int ans1 = L[r];
		if (ans1 >= mx_ans) {
			ans.push_back(mx_ans);
		}
		else {
			int ans2 = get(l, r - L[r]);
			int fans = min(mx_ans, max(ans1, ans2));
			ans.push_back(fans);
		}
	}	
}

void write() {
	for (auto i : ans)
		cout << i << endl;
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