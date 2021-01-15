#include <bits/stdc++.h>
 
using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
struct person{
	int a, b, ind;
	person() {}
	person(int x, int y, int z) {
		a = x, b = y, ind = z;
	}
};
 
int n, k;
vector<int> t;
vector<person> a;
void read() {
	cin >> n >> k;
	t.resize(k);
	for (auto &i : t)
		cin >> i;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].a >> a[i].b;
		a[i].ind = i;
	}
}
 
vector<int> ans;
 
struct event{
	int ind, time, need;
	event() {}
	event(int a, int b, int c) {
		time = a, need = b, ind = c;
	}
};
 
bool operator<(const event & a, const event & b) {
	return tie(a.time, a.need, a.ind) < tie(b.time, b.need, b.ind);
}
 
vector<int> Next;
 
void run() {
	ans.assign(n, 0);
	set<event> q;
	for (auto i : a) {
		q.insert({i.a, 0, i.ind});
	}
 
	Next.assign(k, 0);
	while (!q.empty()) {
		auto x = *q.begin();
		q.erase(q.begin());
		x.time = max(Next[x.need], x.time) + t[x.need];
		
		if (a[x.ind].b != 0 && a[x.ind].b < x.time - a[x.ind].a) {
			ans[x.ind] = -1;
			x.time = a[x.ind].a + a[x.ind].b;
			Next[x.need] = max(x.time, Next[x.need]);
			continue;
		}
 
		Next[x.need] = x.time;
		x.need++;
		
		if (x.need == k) {
			if (a[x.ind].b == 0 || a[x.ind].b >= x.time - a[x.ind].a)
				ans[x.ind] = x.time - a[x.ind].a;
			else
				ans[x.ind] = -1;
		} 
		else {
			q.insert(x);
		}
	}
}
 
void write() {
	for (auto i : ans)
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