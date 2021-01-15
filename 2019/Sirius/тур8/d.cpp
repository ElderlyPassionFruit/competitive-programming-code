#include <bits/stdc++.h>

using namespace std;

struct point
{
	int x, y;
	point() {
		x = y = 0
	}	
	point(int a, int b) {
		x = a, y = b;
	}
};

point operator-(const point & a, const point & b) {
	point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int sq(int x) {
	return x * x;
}

int dist(point a) {
	return sq(a.x) + sq(a.y);
}

int dist(point a, point b) {
	return dist(a - b);
}

point p0;

bool cmp(pair <point, int> a, pair <point, int> b) {
	a.first = a.first - p0;
	b.first = b.first - p0;
	if ((a.first ^ b.first) == 0) {
		return dist(a.first) < dist(b.first);
	}
	return (a.first ^ b.first) > 0; 
}
#define vec point
vector <pair <point, int> > convex_hull(vector <pair <point, int> > g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[i].first.y < g[0].first.y || (g[i].first.y == g[0].first.y && g[i].first.x < g[0].first.x))
			swap(g[i], g[0]);
	}
	p0 = g[0].first;
	sort(g.begin() + 1, g.end(), cmp);
	vector <pair <point, int> > hull;
	hull.push_back(p0);
	for (int i = 1; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec p1 = hull[last].first - hull[last - 1].first;
			vec p2 = g[i].first - hull[last];
			if ((p1 ^ p2) > 0)
				break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}
vector <pair <point, int> > help;
const int MAXN = 1510;
int pos[MAXN][2];
int n;
void read() {
	cin >> n;
	help.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> pos[i][0] >> pos[i][1];
		help[i].first.x = pos[i][0];
		help[i].first.y = pos[i][1];
		help[i].second = i;
	}
	help = convex_hull(help);
}

const int INF = 1e6;

map<int, int> dist[MAXN];

bool check(int i, int j) {
	return (pos[i][0] < pos[j][0] && pos[i][1] < pos[j][1]) || (pos[i][0] > pos[j][0] && pos[i][1] > pos[j][1]);
}

map <int, int> solve(int u) {
	vector <int> dist1(n, INF);
	deque <pair <int, int> > q1;
	dist1[u] = 0;
	q1.push_back({0, u});

	while (!q1.empty()) {
		auto p = q1[0];
		int v = p.second;
		int d = p.first;
		q1.pop_front();
		for (auto i : g[v]){
			if (dist1[i] > d + 1) {
				dist1[i] = d + 1;
				q1.push_back({dist1[i], i});
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += dist1[i];
	}
	return ans;
}


void make() {

}

vector <int> g[MAXN];

void run() {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (check(i, j)){
				g[i].push_back(j);
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << solve(i) << " ";
} 

signed main() {
	freopen("adriatic.in", "r", stdin);
	freopen("adriatic.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}