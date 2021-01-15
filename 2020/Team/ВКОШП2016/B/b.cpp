#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct event {
	int timee, typee;
	int pass;

	event(int timee, int typee, int pass) : timee(timee), typee(typee), pass(pass) {};
};

bool operator<(const event& a, const event &b) {
	if (a.timee != b.timee)
		return a.timee < b.timee;
	if (a.typee != b.typee) {
		return a.typee < b.typee;
	}
	return a.pass < b.pass;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m, k;
	cin >> n >> m >> k;
	vector<pair<int, int>> times(k);
	for (int i = 0; i < k; i++) {
		cin >> times[i].first >> times[i].second;
	}
	set<int> s;
	map<int, int> mm; // {pass, place}
	map<int, int> timew;
	for (int i = 0; i < 2 * m - 1; i++) {
		s.insert(i);
	}
	vector<event> events;
	for (int i = 0; i < k; i++) {
		events.push_back(event(times[i].first, 1, i));
		events.push_back(event(times[i].second, -1, i));
	}
	sort(events.begin(), events.end());
	for (int i = 0; i < (int) events.size(); i++) {
		auto e = events[i];
		if (e.typee == -1) {
			//cout << e.timee << " - " << e.pass << endl;
			timew[mm[e.pass]] += times[e.pass].second - times[e.pass].first;
			s.insert(mm[e.pass]);
		} else {
			if (s.empty()) {
				mm[e.pass] = INT_MAX;
				continue;
			}
			int indd = *s.begin();
			s.erase(s.begin());
			mm[e.pass] = indd;
			//cout << e.timee << " + " << e.pass << " " << indd << endl;
		}
	}
	int minn = INT_MAX;
	int best = -1;
	for (int i = m - 1; i < 2 * m - 1; i++) {
		if (timew[i] < minn) {
			minn = timew[i];
			best = i;
		}
	}
	//for (auto el : timew) {
	//	cout << el.first << " " << el.second << endl;
	//}
	cout << minn << " " << best - (m - 1) + 1 << endl;
	return 0;
}