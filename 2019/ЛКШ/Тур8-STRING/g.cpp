#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

typedef vector<int> lnum;

lnum sum(lnum a, lnum b) {
	int sz = max(a.size(), b.size()) + 1;
	lnum ans(sz, 0);
	while(a.size() < sz)
		a.push_back(0);
	while(b.size() < sz)
		b.push_back(0);

	for (int i = 0; i < ans.size() - 1; i++) {
		ans[i] = ans[i] + a[i] + b[i];
		ans[i + 1] = ans[i + 1] + ans[i] / 10;
		ans[i] = ans[i] % 10;
	}
	while (ans.size() > 1 && ans.back() == 0)
		ans.pop_back();
	return ans;
}

void wr(lnum a) {
	reverse(a.begin(), a.end());
	for (auto i : a)
		cout << i;
}

const int MAXN = 110;

struct node{
	map <int, node*> lett, go;
	node * suff;
	bool term;
	lnum dp[MAXN]; 
	node() {
		for (int i = 0; i < MAXN; i++)
			dp[i] = {0};
		term = false;
		suff = nullptr;
	}
};

void add(node * tree, vector<int> s) {
	for (int i = 0; i < s.size(); i++) {
		if (tree->lett.find(s[i]) == tree->lett.end())
			tree->lett[s[i]] = new node();
		tree = tree->lett[s[i]];
	}
	tree->term = true;
}

struct event{
	node * tree, * par;
	int type;
	int lett;
	event(node * a, node * b, int c, int d) {
		tree = a, par = b, type = c, lett = d;
	}
};

bool check(node * tree, int x) {
	return tree->lett.find(x) != tree->lett.end();
}

void bfs(node * tree, int len) {
	deque<event> q;
	q.push_back({tree, tree, 0, 0});
	while (!q.empty()) {
		node * tree = q[0].tree;
		node * par = q[0].par;
		int type = q[0].type;
		int lett = q[0].lett;
		q.pop_front();
		if (type == 0) {
			tree->suff = tree;
			for (int i = 0; i < len; i++) {
				if (check(tree, i))
					tree->go[i] = par->lett[i];
				else
					tree->go[i] = par;
			}
		}
		else if (type == 1) {
			tree->suff = par;
			for (int i = 0; i < len; i++) {
				if (check(tree, i))
					tree->go[i] = tree->lett[i];
				else
					tree->go[i] = tree->suff->go[i];
			}
		}
		else {
			tree->suff = par->suff->go[lett];
			for (int i = 0; i < len; i++) {
				if (check(tree, i))
					tree->go[i] = tree->lett[i];
				else
					tree->go[i] = tree->suff->go[i];
			}
		}
		tree->term |= tree->suff->term;

		for (int i = 0; i < len; i++)
			if (check(tree, i))
				q.push_back(event(tree->lett[i], tree, type + 1, i));
	}
}

void dfs(node * tree, int len, int it) {
	for (int i = 0; i < len; i++) {
		if (tree->go[i]->term)
			continue;
		tree->go[i]->dp[it] = sum(tree->go[i]->dp[it], tree->dp[it - 1]);
	}

	for (auto i : tree->lett) {
		if (i.second->term)
			continue;
		dfs(i.second, len, it);
	}
}

void make_ans(node * tree, lnum & ans, int it) {
	ans = sum(ans, tree->dp[it]);
	for (auto i : tree->lett) {
		if (i.second->term)
			continue;
		make_ans(i.second, ans, it);
	}
}

int n, m, p;
node * tree;

void read() {
	tree = new node();
	cin >> n >> m >> p;
	string lett;
	cin >> lett;
	set<char> help;
	for (auto i : lett)
		help.insert(i);
	map <char, int> coord;
	int cnt = 0;
	for (auto i : help)
		coord[i] = cnt++;

	for (int i = 0; i < p; i++) {
		string x;
		cin >> x;
		vector<int> t;
		for (auto j : x)
			t.push_back(coord[j]);
		add(tree, t);
	}
	bfs(tree, n);
}

lnum ans;

void run() {
	tree->dp[0] = {1};
	for (int i = 1; i <= m; i++)
		dfs(tree, n, i);
	ans = {0};
	make_ans(tree, ans, m);
}

void write() {
	wr(ans);
	cout << endl;
}

signed main() {
	freopen("censored.in", "r", stdin);
	freopen("censored.out", "w", stdout);

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}