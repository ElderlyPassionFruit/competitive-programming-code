#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	node *l, *r;
	int pos;
	int next;
	node(int n_pos, int n_next) {
		pos = n_pos;
		next = n_next;
		l = nullptr;
		r = nullptr;
	}
};

int n, m, p;
string s;

void read() {
	cin >> n >> m >> p >> s;
	//cout << "n = " << n << " m = " << m << " p = " << p << "\ns = " << s << endl;
	p--;
}	

node * add(node * tree_l, node * tree_r) {
	if (tree_l != nullptr)
		tree_l->r = tree_r;
	if (tree_r != nullptr)
		tree_r->l = tree_l;
	return tree_l;
}

node * make() {
	vector<int> my_next(n);
	vector<int> st;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			st.push_back(i);
		}
		else {
			my_next[st.back()] = i;
			my_next[i] = st.back();
			st.pop_back();
		}
	}
	
	node * tree = nullptr;
	for (int i = n - 1; i >= 0; i--) {
		tree = add(new node(i, my_next[i]), tree);
	}

	for (int i = 0; i < p; i++)
		tree = tree->r;
	return tree;
}

node * go_l(node * tree) {
	assert(tree != nullptr);
	return tree->l;
}

node * go_r(node * tree) {
	assert(tree != nullptr);
	return tree->r;
}

void make (node * tree_l, node * tree_r) {
	if (tree_l->l != nullptr) {
		tree_l->l->r = tree_r->r;
	}
	if (tree_r->r != nullptr) {
		tree_r->r->l = tree_l->l;
	}
}

node * del(node * tree) {
	node * help = tree;
	while (tree->next > help->pos) {
		help = help->r;
	}
	while (tree->next < help->pos) {
		help = help->l;
	}
	if (help->pos < tree->pos) {
		make(help, tree);
		if (tree->r != nullptr)
			return tree->r;
		else
			return help->l;
	}
	else {
		make(tree, help);
		if (help->r != nullptr)
			return help->r;
		else
			return tree->l;
	}
}

string make_ans(node * tree) {
	string ans = "";
	while (tree != nullptr) {
		ans += s[tree->pos];
		tree = tree->r;
	}
	return ans;
}

void wr(node * tree) {
	if (tree == nullptr)
		return;
	cout << tree->pos << " " << tree->next << endl;
	wr(tree->r);
}

node * get_l(node * tree) {
	while (tree->l != nullptr)
		tree = tree->l;
	return tree;
}

string ans;

void run() {
	node * tree = make();
	//cout << "tree = " << endl;
	//wr(tree);
	//cout << endl;
	string help;
	cin >> help;
	for (auto i : help) {
		if (i == 'L') {
			tree = go_l(tree);
		}	
		if (i == 'R') {
			tree = go_r(tree);
		}
		if (i == 'D') {
			tree = del(tree);
		}
		//wr(tree);
		//cout << endl;
	}

	ans = make_ans(get_l(tree));
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