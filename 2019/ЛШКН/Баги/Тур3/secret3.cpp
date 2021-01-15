/*
	Secret Data Structure Problem (secret3)
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
#define mp make_pair
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Segm {
	int w, id;

	Segm() : w(), id() {}
	Segm(int _w, int _id) : w(_w), id(_id) {}

	bool operator < (const Segm &S) const {
		return w < S.w;
	}
};
struct Event {
	int x, t, id;

	Event() : x(), t(), id() {}
	Event(int _x, int _t, int _id) : x(_x), t(_t), id(_id) {}

	bool operator < (const Event &e) const {
		if (x != e.x) return x < e.x;
		return t < e.t;
	}
};

const int N = 100100;
int w[N];
set<Segm> setik;
vector<Event> ev;
int ans[N];

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		int l, r;
		scanf("%d%d%d", &l, &r, &w[i]);
		ev.push_back(Event(l, -1, i));
		ev.push_back(Event(r, 1, i));
	}
	for (int i = 0; i < m; i++) {
		int x;
		scanf("%d", &x);
		ev.push_back(Event(x, 0, i));
	}
	sort(ev.begin(), ev.end());
	for (Event e : ev) {
		if (e.t == -1) {
			setik.insert(Segm(w[e.id], e.id));
		} else if (e.t == 0) {
			if (setik.empty())
				ans[e.id] = -1;
			else
				ans[e.id] = setik.begin()->w;
		} else {
			setik.erase(Segm(w[e.id], e.id));
		}
	}
	for (int i = 0; i < m; i++)
		printf("%d\n", ans[i]);

	return 0;
}
