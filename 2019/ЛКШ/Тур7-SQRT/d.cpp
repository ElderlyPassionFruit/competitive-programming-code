#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
const int MAXC = 1e6 + 10;

struct event{
	int l, r, ind;
	event() {
		l = 0, r = 0, ind = 0;
	}
	event(int a, int b, int c) {
		l = a, r = b, ind = c;
	}
};

int sq;

bool cmp(event a, event b) {
	if (a.l / sq != b.l / sq)
		return a.l < b.l;
	return a.r < b.r;
}

int n, t;
int a[MAXN];
long long cnt[MAXC];
long long ans[MAXN];
vector<event> query;

void read() {
	cin >> n >> t;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sq = sqrt(t);
	for (int i = 0; i < t; i++) {
		event x;
		cin >> x.l >> x.r;
		x.l--;
		x.r--;
		x.ind = i;
		query.push_back(x);
	}
	sort(query.begin(), query.end(), cmp);
}

long long fans = 0;

void add(int pos) {
	fans -= cnt[a[pos]] * cnt[a[pos]] * a[pos];
	cnt[a[pos]]++;
	fans += cnt[a[pos]] * cnt[a[pos]] * a[pos];
}

void del(int pos) {
	fans -= cnt[a[pos]] * cnt[a[pos]] * a[pos];
	cnt[a[pos]]--;
	fans += cnt[a[pos]] * cnt[a[pos]] * a[pos];
}

long long get_ans() {
	return fans;
}

void run() {
	int l = 0, r = -1;
	for (int i = 0; i < t; i++) {
		while (l > query[i].l) {
			l--;
			add(l);
		}
		while (r < query[i].r) {
			r++;
			add(r);
		}
		while (l < query[i].l) {
			del(l);
			l++;
		}
		while (r > query[i].r) {
			del(r);
			r--;
		} 
		ans[query[i].ind] = get_ans();
	}
}

void write() {
	for (int i = 0; i < t; i++) {
		cout << ans[i] << "\n";
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