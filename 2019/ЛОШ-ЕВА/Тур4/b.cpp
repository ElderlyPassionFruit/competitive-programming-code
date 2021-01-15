#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m, p;
map <int, pair <vector<int>, vector<int> > > pos;
vector<pair <int, int> > people;
int pos_now = 1e9;
void read() {
	cin >> n >> m >> p;
	for (int i = 0; i < n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		pos_now = min(pos_now, c);
		pos[c].first.push_back(i);
		pos[d].second.push_back(i);
		people.push_back({a, b});
	}
}


int sum;
int ans;

multiset <pair <int, int> > fa, fb;

void add(int ind) {
	int a = people[ind].first, b = people[ind].second;
	if (b >= a) {
		sum += b;
		return;
	}
	if (fa.empty()) {
		sum += a;
		fa.insert({a - b, ind});
		return;
	}

	sum += a;
	fa.insert({a - b, ind});
	if (fa.size() > m) {
		auto p = *fa.begin();
		sum -= p.first;
		fa.erase(fa.begin());
		fb.insert({-p.first, p.second});
	}
}

void del(int ind) {
	int a = people[ind].first, b = people[ind].second;
	if (b >= a) {
		sum -= b;
		return;
	}
	auto it1 = fa.find({a - b, ind});
	if (it1 != fa.end()) {
		sum -= a;
		fa.erase(it1);
		
		if (!fb.empty()) {
			auto p = *fb.begin();
			fb.erase(fb.begin());
			sum += -p.first;
			fa.insert({-p.first, p.second});
		}
		return;
	}

	auto it2 = fb.find({b - a, ind});
	if (it2 != fb.end()) {
		sum -= b;
		fb.erase(it2);
	}
}

void run() {
	ans = 0;
	sum = 0;
	for (auto i : pos) {
		ans += (i.first - pos_now) * sum;
		pos_now = i.first;
		for (auto j : i.second.first)
			add(j);
		for (auto j : i.second.second)
			del(j);
	}
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