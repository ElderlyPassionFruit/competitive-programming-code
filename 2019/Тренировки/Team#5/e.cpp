#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> p;

void read() {
	cin >> n >> k;
	p.resize(n);
	for (auto &i : p)
		cin >> i;
}

struct event{
	int p, c, ind;
};

bool operator<(event a, event b) {
	int x = a.p * a.c;
	int y = b.p * b.c;
	return tie(x, a.ind) < tie(y, b.ind);
}

vector<int> ans;
const int MAXN = 1e5 + 10;
vector<int> nums[MAXN];

int calc(int ind) {
	if (nums[ind].size() == 0)
		return 0;
	else if (nums[ind].size() == 1)
		return nums[ind][0] * 2;
	else
		return nums[ind][nums[ind].size() - 1] + nums[ind][nums[ind].size() - 2];
}

void run() {
	set <event> q;
	for (int i = 1; i <= k; i++) {
		q.insert({0, 0, i});
	}

	ans.resize(n);

	for (int i = 0; i < n; i++) {
		auto x = *q.begin();
		q.erase(q.begin());
		nums[x.ind].push_back(p[i]);
		ans[i] = x.ind;
		x.c++;
		x.p = calc(x.ind);
		q.insert(x);
	}
}

void write() {
	for (auto &i : ans)
		cout << i << " ";
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