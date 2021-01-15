// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int curIND = 1;

struct kek {
	string s;
	int cur_ind;
	int ind;

	kek() {
		s=  "";
		cur_ind = 0;
		ind = -1;
	}

	kek(string s) : s(s) {
		cur_ind = 0;
		ind = curIND++;
	}
};

struct node {
	node *go[26];
	vector<kek *> need[26];
	bool term;

	node() {
		for (int i = 0; i < 26; i++) {
			go[i] = NULL;
			need[i] = {};
		}
		term = false;
	}
};

node *root;

set<int> cur_ans;

void push(node *n, char c) {
	if (c == 0) {
		for (int i = 0; i < 26; i++) {
			if (n->go[i] != NULL) {
				auto kek = n->need[i];
				n->need[i].clear();
				for (auto el : kek) {
					if (el->cur_ind == (int) el->s.size()) {
						cur_ans.insert(el->ind);
					} else if (n->go[i]->term) {
						if(el->cur_ind== el->s.size() - 1)
						{
							cur_ans.insert(el->ind);
							continue;
						}
						root->need[el->s[++el->cur_ind] - 'a'].push_back(el);
						push(root, el->s[el->cur_ind]);
					} else {
						if(el->cur_ind== el->s.size() - 1)
						{
						//	cur_ans.insert(el->ind);
							continue;
						}
						n->go[i]->need[el->s[++el->cur_ind] - 'a'].push_back(el);
						push(n->go[i], el->s[el->cur_ind]);
					}
				}
			}
		}

	} else {
		for (int i = c - 'a'; i <= c - 'a'; i++) {
			if (n->go[i] != NULL) {
				auto kek = n->need[i];
				n->need[i].clear();
				for (auto el : kek) {
					if (el->cur_ind == (int) el->s.size()) {
						cur_ans.insert(el->ind);
					} else if (n->go[i]->term) {
						if(el->cur_ind== el->s.size() - 1)
						{
							cur_ans.insert(el->ind);
							continue;
						}
						root->need[el->s[++el->cur_ind] - 'a'].push_back(el);
						push(root, el->s[el->cur_ind]);
					} else {
						if(el->cur_ind== el->s.size() - 1)
						{
					//		cur_ans.insert(el->ind);
							continue;
						}
						n->go[i]->need[el->s[++el->cur_ind] - 'a'].push_back(el);
						push(n->go[i], el->s[el->cur_ind]);
					}
				}
			}
		}
	}
}

void addString(string s) {
	node *cur = root;
	int i = 0;
	for (char c : s) {
		if (cur->go[c - 'a'] == NULL) {
			cur->go[c - 'a'] = new node();
			if (i == (int) s.size() - 1) {
				cur->go[c - 'a']->term = 1;
			}
			push(cur, c);
		}
		cur = cur->go[c - 'a'];
		i++;
	}
	push(cur, 0);
	// for (int i = 0; i < 26; i++) {
	// 	for (auto el : cur->need[i]) {
	// 		cur_ans.insert(el->ind);
	// 	}
	// 	cur->need[i].clear();
	// }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	root = new node();
	int k = 0;
	while (n--) {
		char c;
		cin >> c;
		string s;
		cin >> s;
		rotate(s.begin(), s.begin() + k % s.size(), s.end());
		if (c == '+') {
			addString(s);
		} else {
			
			root->need[s[0] - 'a'].push_back(new kek(s));
			push(root, s[0]);
		}
		cout << cur_ans.size() << " ";
		k = cur_ans.size();
		for (int el : cur_ans) {
			cout << el << " ";
		}
		cout << endl;
		cur_ans.clear();
	}
	return 0;
}