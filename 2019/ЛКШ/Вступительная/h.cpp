#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double



signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	multiset <double> t, d;
	for (int i = 0; i < n; i++) {
		char type;
		double x;
		cin >> type >> x;
		if (type == 'T') t.insert(x);
		else d.insert(x);
	}

	double time_now = 0, dist = 0, speed = 1;

	while (!t.empty() && !d.empty()) {
		double last_t = *t.begin();
		double last_d = *d.begin();
		double delta_t = last_t - time_now;
		double delta_d = last_d - dist;

		if (delta_d * speed < delta_t) {
			dist = last_d;
			time_now += delta_d * speed;
			d.erase(d.begin());
		}
		else {
			time_now = last_t;
			dist += delta_t / speed;
			t.erase(t.begin());
		}
		speed = speed + 1;
	}

	while (!t.empty()) {
		double last_t = *t.begin();
		double delta_t = last_t - time_now;
		time_now = last_t;
		dist += delta_t / speed;
		t.erase(t.begin());
		speed = speed + 1;
	}

	while (!d.empty()) {
		double last_d = *d.begin();
		double delta_d = last_d - dist;
		dist = last_d;
		time_now += delta_d * speed;
		d.erase(d.begin());
		speed = speed + 1;
	}

	time_now += (1000.0 - dist) * speed;
	cout << (int) round(time_now) << endl;
	
	return 0;
}