#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int x, type, ind;
};

bool operator<(event a, event b) {
	return tie(a.x, a.type, a.ind) < tie(b.x, b.type, b.ind);
}

int n;
vector<event> have;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		event x;
		cin >> x.x;
		x.ind = i;
		x.type = 1;
		have.push_back(x);
	}
	for (int i = 0; i < n; i++) {
		event x;
		cin >> x.x;
		x.ind = i;
		x.type = 2;
		have.push_back(x);
	}
	sort(have.begin(), have.end());
}

vector<pair <int, int> > ans;

struct fset{
	int dist, pos1, pos2;
};

bool operator<(fset a, fset b) {
	return tie(a.dist, a.pos1, a.pos2) < tie(b.dist, b.pos1, b.pos2);
}

set<fset> segs;
set<int> pos;

void add(int pos1, int pos2) {
	if (!pos.count(pos1) || !pos.count(pos2)) return;
	if (have[pos1].type == have[pos2].type) return;
	segs.insert({abs(have[pos1].x - have[pos2].x), pos1, pos2});
}

pair <int, int> get_ans() {
	/*cout << "segs = " << endl;
	for (auto i : segs) {
		cout << i.dist << " " << i.pos1 << " " << i.pos2 << endl;
	}
	cout << endl;*/
	while (!segs.empty()) {
		auto t = *segs.begin();
		segs.erase(segs.begin());
		if (!pos.count(t.pos1) || !pos.count(t.pos2)) continue;
		
		pair <int, int> fans = {have[t.pos1].ind, have[t.pos2].ind};
		//cout << "fans = " << fans.first << " " << fans.second << endl;
		if (have[t.pos1].type == 2)
			swap(fans.first, fans.second);

		pos.erase(t.pos1);
		pos.erase(t.pos2);
		auto posL = pos.lower_bound(t.pos1);
		auto posR = pos.lower_bound(t.pos2);
		if (posL == pos.begin())
			return fans;
		if (posR == pos.end())
			return fans;
		--posL;
		add(*posL, *posR);
		return fans;
	}
	assert(false);
}

void run() {
	for (int i = 0; i < 2 * n; i++)
		pos.insert(i);

	for (int i = 0; i < 2 * n - 1; i++) {
		add(i, i + 1);
	}
	
	/*cout << "have = " << endl;
	for (auto i : have) {
		cout << i.x << " " << i.type << " " << i.ind << endl;
	}
	*/
	

	for (int i = 0; i < n; i++) {
		ans.push_back(get_ans());
	}
}

void write() {
	for (auto i : ans) {
		cout << i.first + 1 << " " << i.second + 1 << endl;
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