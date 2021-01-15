#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

vector<int> have = {1, 2, 3, 4, 5, 6};
int n, b, k, q, s;

vector<int> make_ans(vector<int> p) {
	for (auto &i : p) {
		i--;
	}
	vector<vector<int>> ans(b);
	for (int i = 0; i < n; i++) {
		ans[i / k].push_back(p[i]);
	}
	for (int i = 0; i < b; i++) {
		shuffle(all(ans[i]), rnd);
	}
	shuffle(all(ans), rnd);
	vector<int> ret;
	for (auto i : ans) {
		for (auto j : i) {
			ret.push_back(have[j]);
		}
	}
	return ret;
}

vector<int> query(vector<int> p) {
	cout << "? ";
	for (auto i : p)
		cout << i << " ";
	cout << endl;
	vector<int> ans(p.size());
	//for (auto &i : ans)
	//	cin >> i;
	ans = make_ans(p);
	return ans;
}

void out_ans(vector<int> ans) {
	cout << "! ";
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	exit(0);
}


void read() {
	cin >> n >> b >> k >> q >> s;
}

namespace solver_group_2_4{
	int n, b, k;
	void init(int _n, int _b, int _k) {
		n = _n, b = _b, k = _k;
	}

	vector<vector<int>> g;
	void build_graph(vector<int> ans1, vector<int> ans2) {
		g.resize(n + 1);
		for (int i = 0; i < n; i += 2) {
			int u = ans1[i], v = ans1[i + 1];
			g[u].push_back(v);
			g[v].push_back(u);
			u = ans2[i], v = ans2[i + 1];
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}

	set<pair<int, int>> build_set(vector<int> ans1) {
		set<pair<int, int>> ans;
		for (int i = 0; i < n; i += 2) {
			ans.insert({min(ans1[i], ans1[i + 1]), max(ans1[i], ans1[i + 1])});
		}
		return ans;
	}

	void build_have(vector<int> p, set<pair<int, int>> & help) {
		vector<int> ans3 = query(p);
		cerr << "ans3 = " << endl;
		for (auto i : ans3)
			cerr << i << " ";
		cerr << endl;
		for (int i = 0; i < n; i += 2) {
			pair<int, int> now = {min(ans3[i], ans3[i + 1]), max(ans3[i], ans3[i + 1])};
			if (help.count(now))
			help.erase(now);
		}
	}

	vector<bool> used;
	vector<int> order;

	void dfs_make(int v) {
		used[v] = true;
		order.push_back(v);
		for (auto i : g[v]) {
			if (used[i]) continue;
			dfs_make(i);
		}
	}

	void solve() {
		vector<int> p(n);
		iota(all(p), 1);
		vector<int> ans1 = query(p);
		p.erase(p.begin());
		p.push_back(1);
		vector<int> ans2 = query(p);

		cerr << "ans1 = " << endl;
		for (auto i : ans1)
			cerr << i << " ";
		cerr << endl;

		cerr << "p = " << endl;
		for (auto i : p)
			cerr << i << " ";
		cerr << endl;

		cerr << "ans2 = " << endl;
		for (auto i : ans2)
			cerr << i << " ";
		cerr << endl; 

		build_graph(ans1, ans2);

		auto have = build_set(ans1);

		cerr << "have = " << endl;
		for (auto i : have) {
			cerr << i.first << " " << i.second << endl;
		}
		cerr << endl;

		iota(all(p), 1);
		p[0] = 1;
		p[1] = 3;
		p[2] = 2;
		p[3] = 4;
		build_have(p, have);

		//assert(have.size() == 2);

		cerr << "have это должно быть 1 2 3 4 " << endl;
		for (auto i : have)
			cerr << i.first << " " << i.second << endl;
		cerr << endl;

		auto fbuild = build_set(ans1);
		iota(all(p), 1);
		p[0] = 1;
		p[1] = 5;
		p[4] = 2;
		p[5] = 6;
		

		build_have(p, fbuild);

		cerr << "fbuild это должно быть 1 2 5 6 " << endl;
		for (auto i : fbuild)
			cerr << i.first << " " << i.second << endl;
		cerr << endl;

		//assert(fbuild.size() == 2);

		set<int> Pair_1_2;
		for (auto i : have) {
			Pair_1_2.insert(i.first);
			Pair_1_2.insert(i.second);
		}
		set<int> have_1234 = Pair_1_2;
		Pair_1_2.clear();

		for (auto i : fbuild) {
			if (have_1234.count(i.first)) {
				Pair_1_2.insert(i.first);
			}
			if (have_1234.count(i.second)) {
				Pair_1_2.insert(i.second);
			}
		}

		cerr << "Pair_1_2 = " << endl;
		for (auto i : Pair_1_2)
			cerr << i << " ";
		cerr << endl;

		//assert(Pair_1_2.size() == 2);
		int One = -1;
		for (int i = 0; i < n; i += 2) {
			int x = ans2[i], y = ans2[i + 1];
			if (!Pair_1_2.count(x) && !Pair_1_2.count(y)) continue;
			if (have_1234.count(x) && have_1234.count(y)) continue;
			if (Pair_1_2.count(x))
				One = x;
			else 
				One = y;
			break;
		}
		//assert(One != -1);
		int Two = One;
		for (auto i : Pair_1_2)
			Two ^= i;
		used.assign(n + 1, false);
		used[One] = true;
		order.push_back(One);
		dfs_make(Two);
		out_ans(order);
	}
}

namespace solver_group_1_5{
	int n, b, k;
	void init(int _n, int _b, int _k) {
		n = _n, b = _b, k = _k;
	}

	int get_type(int x, vector<int> ans) {
		for (int i = 0; i < n / 2; i++) {
			if (ans[i] == x) {
				return 0;
			}
		}
		return 1;
	}

	void solve() {
		vector<int> p(n);
		iota(all(p), 1);
		vector<int> ans1 = query(p);

	    p = {1, 4, 5, 2, 3, 6};
		vector<int> ans2 = query(p);

		cout << "ans1 = " << endl;
		for (auto i : ans1)
			cout << i << " ";
		cout << endl;
		cout << "ans2 = " << endl;
		for (auto i : ans2)
			cout << i << " ";
		cout << endl;

		set<int> have16;
		vector<int> type;
		for (auto i : ans2) {
			type.push_back(get_type(i, ans1));
		}
		vector<int> cnt(b);
		for (int i = 0; i < n; i++) {
			cnt[i / k] += type[i];
		}

		cout << "cnt = " << endl;
		for (auto i : cnt)
			cout << i << " ";
		cout << endl;

		if (cnt[0] == 1) {
			for (int i = 0; i < n / 2; i++) {
				if (type[i] == 1) {
					have16.insert(ans2[i]);
				} 
			}
			for (int i = n / 2; i < n; i++) {
				if (type[i] == 0) {
					have16.insert(ans2[i]);
				} 
			}
		} else {
			for (int i = 0; i < n / 2; i++) {
				if (type[i] == 0) {
					have16.insert(ans2[i]);
				} 
			}
			for (int i = n / 2; i < n; i++) {
				if (type[i] == 1) {
					have16.insert(ans2[i]);
				} 
			}
		}
		assert(have16.size() == 2);

		cout << "have16 = " << endl;
		for (auto i : have16)
			cout << i << " ";
		cout << endl;

		p = {1, 2, 6, 3, 4, 5};
		vector<int> ans3 = query(p);

		cnt.clear();
		for (int i = 0; i < n; i++) {
			cnt[i / k] += get_type(ans3[i], ans1);
		}

		cout << "ans3 = " << endl;
		for (auto i : ans3)
			cout << i << " ";
		cout << endl;

		int Three = -1;
		if (cnt[0] == 2) {
			for (int i = 0; i < n / 2; i++) {
				if (get_type(ans3[i], ans1) == 0) {
					Three = ans3[i];
				}
			}
		} else {
			for (int i = n / 2; i < n; i++) {
				if (get_type(ans3[i], ans1) == 1) {
					Three = ans3[i];
				}
			}
		}

		cout << "Three = " << Three << endl;

		p = {1, 3, 6, 2, 4, 5};
		ans3 = query(p);

		cnt.clear();
		for (int i = 0; i < n; i++) {
			cnt[i / k] += get_type(ans3[i], ans1);
		}

		int Two = -1;
		if (cnt[0] == 2) {
			for (int i = 0; i < n / 2; i++) {
				if (get_type(ans3[i], ans1) == 0) {
					Two = ans3[i];
				}
			}
		} else {
			for (int i = n / 2; i < n; i++) {
				if (get_type(ans3[i], ans1) == 0) {
					Two = ans3[i];
				}
			}
		}

		set<int> have_first;
		for (int i = 0; i < 3; i++) {
			have_first.insert(ans1[i]);
		}

		if (have_first.count(Two)) {
			have_first.erase(Two);
			have_first.erase(Three);
		} else {
			have_first.clear();
			for (int i = n / 2; i < n; i++) {
				have_first.insert(ans1[i]);
			}			
			have_first.erase(Two);
			have_first.erase(Three);
		}

		int One = *have_first.begin();
	
		p = {1, 4, 6, 2, 3, 5};
		ans3 = query(p);
		have_first.clear();
		for (int i = 0; i < 3; i++) {
			have_first.insert(ans3[i]);
		}
		int Six;
		have16.erase(One);
		Six = *have16.begin();
		int Four;
		if (have_first.count(One)) {
			have_first.erase(One);
			have_first.erase(Six);
			Four = *have_first.begin();
		} else {
			have_first.clear();
			for (int i = n / 2; i < n; i++) {
				have_first.insert(ans3[i]);
				have_first.erase(One);
				have_first.erase(Six);
				Four = *have_first.begin();
			}
		}

		int Five;
		have_first.clear();
		for (int i = 1; i <= n; i++)
			have_first.insert(i);
		have_first.erase(One);
		have_first.erase(Two);
		have_first.erase(Three);
		have_first.erase(Four);
		have_first.erase(Six);
		Five = *have_first.begin();
		out_ans({One, Two, Three, Four, Five, Six});
	}
}

namespace solver_group_3{
	int n, b, k;
	void init(int _n, int _b, int _k) {
		n = _n, b = _b, k = _k;
	}

	void solve(vector<pair<int, int>> classes) {
		vector<vector<int>> have(n);
		for (auto i : classes) {
			have[i.first].push_back(i.second);
		}
		bool flag = false;
		for (auto i : have) {
			if (i.size() > 1)
				flag = true;
		}
		if (!flag) {
			vector<int> ans;
			for (auto i : have) {
				for (auto j : i)
					ans.push_back(j);
			}
			out_ans(ans);
		}


	}

	void solve() {
		vector<int> p(n);
		iota(all(p), 1);
		vector<int> ans = query(p);

		vector<pair<int, int>> classes;
		for (int i = 0; i < n; i++) {
			classes.push_back({i / k, ans[i]});
		}
		solve(classes);
	}
}


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	if (s == 2 || s == 4) {
		solver_group_2_4::init(n, b, k);
		solver_group_2_4::solve();
	} else if (s == 1 || s == 5) {
		solver_group_1_5::init(n, b, k);
		solver_group_1_5::solve();
	} else if (s == 3) {
		solver_group_3::init(n, b, k);
		solver_group_3::solve();
	}
	return 0;
}