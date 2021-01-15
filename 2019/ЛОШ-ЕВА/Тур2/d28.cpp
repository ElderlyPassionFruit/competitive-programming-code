#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
char lett[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		cin >> lett[i];
}

int sz[MAXN];

bool cmp(int a, int b) {
	return sz[a] > sz[b];
}

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

void merge(map <int, int> &a, map<int, int> b) {
	for (auto i : b)
		a[i.first] += i.second;
}

map<int, int> dfs(int v, int p, int num) {
	map<int, int> ans;
	num ^= 1 << (lett[v] - 'a');
	bool flag = false;
	for (auto i : g[v]) {
		if (i != p && !flag){
			ans = dfs(i, v, num);
			flag = true;
		}
		else if (i != p && flag) {
			auto help = dfs(i, v, num);
			merge(ans, help);
		}
	}
	ans[num]++;
	return ans;
}

void fsort() {
	for (int i = 0; i < n; i++)
		sort(g[i].begin(), g[i].end(), cmp);
}

vector<int> good(int mask, char help) {
	mask ^= 1 << (help - 'a');
	vector <int> ans;
	ans.push_back(mask);
	for (int i = 0; i < 26; i++) {
		ans.push_back(mask ^ (1 << i));
	}	
	return ans;
}

unordered_set<int> good_nums;
	

bool check(int a, int b, char c) {
	return good_nums.count(a ^ b ^ (1 << (c - 'a')));
}

string make(int n) {
	string ans = "";
	while (n) {
		ans += '0' + n % 2;
		n /= 2;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int ans[MAXN];

void run() {
	good_nums.insert(0);
	for (int i = 0; i < 26; i++)
		good_nums.insert(1 << i);

	for (int i = 0; i < n; i++) {
		dfs_sz(i, -1);

		fsort();
		
		vector<map <int, int> > help;
		for (auto j : g[i]) {
			help.push_back(dfs(j, i, 0));
		}
		
		/*cout << "i = " << i << endl;
		cout << "help = " << endl;
		for (auto j : help) {
			for (auto k : j) {
				cout << make(k.first) << " " << k.second << endl;
			}
			cout << endl;
		}
*/
		int fans = 0;
		

		for (int s = 0; s < help.size(); s++) {
			for (auto mask_a : help[s]) {
				if (check(mask_a.first, 0, lett[i])) 
					fans += mask_a.second;
			}
		}
		
		/*
		//cout << "masks = " << endl;
		for (int s = 0; s < help.size(); s++) {
			for (int j = s + 1; j < help.size(); j++) {

				int get_fans = 0;
				for (auto mask_a : help[s]) {
					for (auto mask_b : help[j]) {
					//	cout << make(mask_a.first) << " " << make(mask_b.first) << " " << make((1 << (lett[i] - 'a'))) << " " << check(mask_a.first, mask_b.first, lett[i]) << endl;
						if (check(mask_a.first, mask_b.first, lett[i])) {
							get_fans += mask_a.second * mask_b.second; 
						} 
					}
				}
				fans += get_fans;
			}
		}
		*/

		unordered_map <int, int> others;
		for (int j = 0; j < help.size(); j++) {
			for (auto mask_b : help[j])
				others[mask_b.first] += mask_b.second;
		}

		for (int s = 0; s < help.size(); s++) {
			for (auto mask_a : help[s]) {
				others[mask_a.first] -= mask_a.second;
			}

			for (auto mask_a : help[s]) {
				auto v = good(mask_a.first, lett[i]);

				for (auto mask_b : v)
					fans += others[mask_b] * mask_a.second;	
			}
		}

		ans[i] = fans + 1;
	}
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
}

signed main() {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}