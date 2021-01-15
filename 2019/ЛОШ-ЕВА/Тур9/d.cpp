#include <bits/stdc++.h>

using namespace std;
#define int long long

vector<vector<char> > ans;

string s;
int pos;

struct node {
	char x;
	node * l, * r;
	int w, h, my_pos;
	node (char new_x, node * new_l, node * new_r) {
		x = new_x;
		l = new_l;
		r = new_r;
		w = 0, h = 0, my_pos = 0;
	}
};

node * get_full_expression();

node * get_element() {
	if (s[pos] == '(') {
		pos++;
		node * tree = get_full_expression();
		pos++;
		return tree;
	}
	else {
		node * tree = new node(s[pos++], nullptr, nullptr);
		return tree;
	}
}

node * get_mult() {
	node * tree = get_element();
	if (s[pos] == '^') {
		pos++;
		tree = new node('^', tree, get_mult());
	}
	return tree;
}

node * get_part() {
	node * tree = get_mult();
	while (s[pos] == '*' || s[pos] == '/') {
		char x = s[pos++];
		tree = new node(x, tree, get_mult());
	}
	return tree;
}

node * get_full_expression() {
	node * tree = get_part();
	while (s[pos] == '+' || s[pos] == '-') {
		char x = s[pos++];
		tree = new node(x, tree, get_part());
	}
	return tree;
}

int w(node * tree) {
	if (tree == nullptr) return 0;
	return tree->w;
}

int h(node * tree) {
	if (tree == nullptr) return 0;
	return tree->h;
}

int my_pos(node * tree) {
	if (tree == nullptr) return 0;
	return tree->my_pos;
}

char x(node * tree) {
	if (tree == nullptr) return ' ';
	return tree->x;
}

void dfs(node * tree) {
	if (tree == nullptr) return;
	if (tree->x >= 'a' && tree->x <= 'z') {
		tree->w = 1;
		tree->h = 1;
		tree->my_pos = 0;
		return;
	}
	dfs(tree->l);
	dfs(tree->r);

	tree->w = w(tree->l) + w(tree->r) + 5;
	tree->h = max(h(tree->l), h(tree->r)) + 2;
	tree->my_pos = w(tree->l) + 2;
}

void make(node * tree, int i, int j) {
	if (tree == nullptr) return;
	if (tree->x >= 'a' && tree->x <= 'z') {
		ans[i][j] = x(tree);
		return;
	}
	make(tree->l, i + 2, j);
	make(tree->r, i + 2, j + w(tree->l) + 5);
	
	ans[i][my_pos(tree->l) + j] = '.';
	ans[i][w(tree->l) + 5 + my_pos(tree->r) + j] = '.';
	ans[i + 1][my_pos(tree->l) + j] = '|';
	ans[i + 1][w(tree->l) + 5 + my_pos(tree->r) + j] = '|';
	
	for (int pos = my_pos(tree->l) + j + 1; pos < w(tree->l) + 5 + my_pos(tree->r) + j; pos++)
		ans[i][pos] = '-';
	
	ans[i][j + my_pos(tree) - 1] = '[';
	ans[i][j + my_pos(tree)] = x(tree);
	ans[i][j + my_pos(tree) + 1] = ']';
}

void read() {
	cin >> s;
	pos = 0;
}

node * fans = nullptr;

void run() {
	fans = get_full_expression();
	dfs(fans);
	ans.assign(h(fans), vector<char> (w(fans), ' '));
	make(fans, 0, 0);
}

void write() {
	for (int i = 0; i < h(fans); i++) {
		for (int j = 0; j < w(fans); j++) {
			cout << ans[i][j];
		}
		cout << endl;
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