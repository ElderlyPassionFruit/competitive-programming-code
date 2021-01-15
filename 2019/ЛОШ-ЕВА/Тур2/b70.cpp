#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<pair <int, int> > segments;

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.second < b.second;
}

void read() {
	cin >> n;
	segments.resize(n);
	for (auto &i : segments)
		cin >> i.first >> i.second;
	sort(segments.begin(), segments.end(), cmp);
	vector <pair <int, int> > help;
	for (int i = 0; i < min(n, 1000LL); i++)
		help.push_back(segments[i]);
	n = min(n, 1000LL);
	segments = help;
	sort(segments.begin(), segments.end());
}

int ans = 1e9;

void run() {
	for (int i = 0; i < n - 1; i++) {
		int fans = segments[i].second;
		
		int pos_l = 0, pos_r = i + 1;
		
		int min_cost_l = segments[pos_l].second, min_cost_r = segments[pos_r].second;
		
		while (pos_l < i) {
			while (pos_r < n - 1 && segments[pos_l].first + segments[i].first > segments[pos_r + 1].first) {
				pos_r++;
				min_cost_r = min(min_cost_r, segments[pos_r].second);
			}

			if (segments[pos_l].first + segments[i].first > segments[pos_r].first) {

				ans = min(ans, segments[pos_l].second + fans + min_cost_r);
			}
			pos_l++;
		}
	}
}

void write() {
	if (ans == 1e9)
		ans = -1;
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