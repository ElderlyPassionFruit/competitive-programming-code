#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 4010;

vector<pair <pair<pair<int, int>, string>, int> > a;
vector<int> g[MAXN];
int n, s, f;
void read() {
	cin >> n >> s >> f;
	s--;
	f--;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first.first.first >> a[i].first.first.second >> a[i].first.second;
		a[i].second = i;
	}
}

bool cmp1(pair <pair <pair <int, int>, string>, int> a, pair <pair <pair <int, int>, string>, int>b) {
	return a.first.second < b.first.second;
}


void make(vector<pair <pair <pair <int, int>, string>, int> > help) {
	int n = help.size();
	for (int i = 0; i < n; i++) {
		int x = help[i].second;
		int y = help[(i + 1) % n].second;
		g[x].push_back(y);
	}	
}

int operator^(pair <int, int> a, pair <int, int> b) {
	return a.first * b.second - a.second * b.first;
}

const int INF = 1e9;

double sq(double x) {
	return x * x;
}

pair <int, int> operator-(pair <int, int> a, pair <int, int> b) {
	return {a.first - b.first, a.second - b.second};
}

double dist(pair <int, int> a) {
	return sqrt(sq(a.first) + sq(a.second));
}

double dist(pair <int, int> a, pair <int, int> b) {
	return dist(a - b);
}

bool check_l(pair <int, int> a, pair <int, int> b) {
	pair <int, int> x1 = {0LL, 0LL};
	x1.first--;
	x1.second--;
	pair <int, int> x2 = {0LL, 0LL};
	x2.first--;
	x2.second++;
	b = b - a;
	if ((x2 ^ b) <= 0) return false;
	if ((x1 ^ b) >= 0) return false;
	return true;
}



bool check_r(pair <int, int> a, pair <int, int> b) {
	pair <int, int> x1 = {0LL, 0LL};
	x1.first++;
	x1.second++;
	pair <int, int> x2 = {0LL, 0LL};
	x2.first++;
	x2.second--;
	b = b - a;
	if ((x2 ^ b) <= 0) return false;
	if ((x1 ^ b) >= 0) return false;
	return true;
}

bool check_u(pair <int, int> a, pair <int, int> b) {
	pair <int, int> x1 = {0LL, 0LL};
	x1.first--;
	x1.second++;
	pair <int, int> x2 = {0LL, 0LL};
	x2.first++;
	x2.second++;
	b = b - a;
	if ((x2 ^ b) < 0) return false;
	if ((x1 ^ b) > 0) return false;
	return true;
}

bool check_d(pair <int, int> a, pair <int, int> b) {
	pair <int, int> x1 = {0LL, 0LL};
	x1.first++;
	x1.second++;
	pair <int, int> x2 = {0LL, 0LL};
	x2.first--;
	x2.second++;
	b = b - a;
	if ((x2 ^ b) < 0) return false;
	if ((x1 ^ b) > 0) return false;
	return true;
}


pair <pair <pair <int, int>, string>, int> now;

pair <pair <pair <int, int>, string>, int> min(pair <pair <pair <int, int>, string>, int> a, pair <pair <pair <int, int>, string>, int> b) {
	if (dist(now.first.first, a.first.first) < dist(now.first.first, b.first.first)) return a;
	if (dist(now.first.first, a.first.first) > dist(now.first.first, b.first.first)) return b;
	if (a.first.first.first < b.first.first.first) return a;
	if (a.first.first.first > b.first.first.first) return b;
	if (a.first.first.second < b.first.first.second) return a;
	if (a.first.first.second > b.first.first.second) return b;
}

int ans;

void run() {
	sort(a.begin(), a.end(), cmp1);
	vector<pair <pair<pair <int, int>, string>, int> > help;
	char lett = '0';
	for (int i = 0; i < n; i++) {
		if (lett != a[i].first.second[0]) {
			make(help);
			help.clear();
			lett = a[i].first.second[0];
		}
		help.push_back(a[i]);
	} 

	make(help);
	help.clear();

	cout << "a = " << endl;
	for (auto i : a) {
		cout << i.first.first.first << " " << i.first.first.second << " " << i.first.second << " " << i.second << endl;
	}
	
	pair <pair <pair <int, int>, string>, int> l, r, u, d;
	for (int i = 0; i < n; i++) {
		now = a[i];
		l.first.first = r.first.first = u.first.first = d.first.first = {INF, INF};
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (check_l(now.first.first, a[j].first.first))
				l = min(l, a[j]);
			if (check_r(now.first.first, a[j].first.first))
				r = min(r, a[j]);
			if (check_d(now.first.first, a[j].first.first))
				d = min(d, a[j]);
			if (check_u(now.first.first, a[j].first.first))
				u = min(u, a[j]);
		}
		if (i == 0) {
			cout << "r = " << r.first.first.first << " " << r.first.first.second << endl;
		}

		if (l.first.first != make_pair(INF, INF)) 
			g[a[i].second].push_back(l.second);
		if (r.first.first != make_pair(INF, INF)) 
				g[a[i].second].push_back(r.second);
		if (u.first.first != make_pair(INF, INF)) 
				g[a[i].second].push_back(u.second);
		if (d.first.first != make_pair(INF, INF)) 
				g[a[i].second].push_back(d.second);
	}

	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : g[i])
			if (i != j)
			cout << j << " ";
		cout << endl;
	}

	vector<int> d1(n, INF);
	d1[s] = 0;
	set<pair<int, int> > q;
	q.insert({0, s});

	while (!q.empty()) {
		auto p = *q.begin();
		int v = p.second;
		int dist = p.first;
		q.erase(q.begin());
		for (auto i : g[v]) {
			if (d1[i] > dist + 1) {
				q.erase({d1[i], i});
				d1[i] = dist + 1;
				q.insert({d1[i], i});
			}
		}
	}

	cout << "d = ";
	for (auto i : d1)
		cout << i << " ";
	cout << endl;

	ans = d1[f];
}

void write() {
	cout << ans << endl;
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