//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct vec{
	int x, y;
	vec() {}
	vec(int a, int b) {
		x = a, y = b;
	}
};

ll operator^(const vec & a, const vec & b) {
	return (ll)a.x * b.y - (ll)a.y * b.x;
}

ll sq(ll x) {
	return x * x;
}

ll dist(vec a) {
	return sq(a.x) + sq(a.y);
}

vec operator+(const vec & a, const vec  & b) {
	return vec(a.x + b.x, a.y + b.y);
}

vec operator-(const vec & a, const vec  & b) {
	return vec(a.x - b.x, a.y - b.y);
}

bool operator<(const vec & a, const vec & b) {
	if ((a ^ b) != 0) return (a ^ b) > 0;
	return dist(a) < dist(b);
}

const int MAXL = 1e6 + 10;
vector<vec> have[MAXL];

void precalc() {
	for (int i = 0; i * i < MAXL; i++) {
		for (int j = 0; j * j + i * i < MAXL; j++) {
			have[i * i + j * j].push_back({i, j});
		}
	}
	for (int i = 0; i < MAXL; i++)
		sort(all(have[i]));
}

struct event{
	vec alpha;
	vec a;
	int ind;
	event() {}
	event(vec z, vec x, int c) {
		alpha = z, a = x, ind = c;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.alpha, a.a, a.ind) < tie(b.alpha, b.a, b.ind);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	precalc();
	
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	
	vector<int> b;
	for (auto i : a) {
		if (!have[i].empty()) {
			b.push_back(i);
		}
	}
	a = b;
	n = a.size();

	pair<ll, int> fans = {0, 0};
	
	int x = 0, y = 0;
	vector<event> q;
	vector<vec> ans(n);
	
	int cnt = 0;
	
	for (auto i : a) {
		x += have[i][0].x;
		y += have[i][0].y;
		for (int j = 1; j < (int)have[i].size(); j++) {
			q.push_back({have[i][j - 1] + have[i][j], have[i][j] - have[i][j - 1], cnt});
		}
		ans[cnt] = have[i][0];
		cnt++;
	}

	sort(all(q));
	
	fans = {sq(x) + sq(y), 0};
	int it = 0;

	for (auto &v : q) {
		it++;
		x += v.a.x;
		y += v.a.y;
		fans = max(fans, make_pair(sq(x) + sq(y), it));
	}

	it = 0;
	
	for (auto &v : q) {
		if (it == fans.second) break;
		it++;
		ans[v.ind] = v.alpha + v.a;
		ans[v.ind].x /= 2;
		ans[v.ind].y /= 2;
	}	

	x = 0, y = 0;
	cout << n + 1 << "\n";
	cout << x << " " << y << "\n";
	for (auto &i : ans) {
		x += i.x;
		y += i.y;
		cout << x << " " << y << "\n"; 
	}
	return 0;
}