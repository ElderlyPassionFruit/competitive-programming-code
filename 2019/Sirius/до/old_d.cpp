#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e5 + 10;
int tree[4*MAXN];

void update(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l)
		return;
	if (tl == l && tr == r) {
		tree[v] = val;
		return;
	}
	int tm = (tl + tr) / 2;
	update(v * 2, tl, tm, l, r, val);
	update(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int get(int v, int tl, int tr, int cnt) {
	if (tl == tr - 1)
		return tl;
	int tm = (tl + tr) / 2;
	if (tree[v * 2] >= cnt)
		return get(v * 2, tl, tm, cnt);
	else
		return get(v * 2 + 1, tm, tr, cnt - tree[v * 2]);
}

void upd(int pos, int val) {
	update(1, 0, MAXN, pos, pos + 1, val);
	//tree[pos] = val;
}

int get(int cnt) {
	return get(1, 0, MAXN, cnt);
	/*for (int i = 0; i < MAXN; i++) {
		cnt -= tree[i];
		if (!cnt)
			return i;
	}
	return 0;*/
}

struct e{
	int type;
	string code;
	int plus;
	int n;
	e() {
		type = 0;
		code = "";
		plus = 0;
		n = 0;
	}
};

bool cmp(const pair <int, int> & a, const pair <int, int> & b) {
	if (a.first != b.first)
		return a.first > b.first;
	return a.second < b.second;
}


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);	
	vector <e> help;
	set <string> for_find;
	int id = 0;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		string type;
		cin >> type;
		if (type == "ISSUE") {
			string code;
			cin >> code;
			e add;
			add.type = 1;
			add.code = code;
			help.push_back(add);
//			cout << endl;
//			cout << "puhh" << endl;
//			for (auto i : help) {
//				cout << i.type << " " << i.code << " " << i.plus << " " << i.n << endl;
//			}
		}
		if (type == "DELETE") {
			string code;
			cin >> code;
			e add;
			add.type = 2;
			add.code = code;
			help.push_back(add);
		}
		if (type == "RELIABILITY") {
			string code;
			int x;
			cin >> code >> x;
			e add;
			add.type = 3;
			add.code = code;
			add.plus = x;
			help.push_back(add); 
		}
		if (type == "FIND") {
			int n;
			cin >> n;
			e add;
			add.type = 4;
			add.n = n;
			help.push_back(add);
		}
	}

	//cout << endl;
	map <string, pair<int, int> > num; 
	vector <pair <int, int> > fhelp;
	map <int, string> fid;
	map <int, int> find;
	for (int i = 0; i < q; i++) {
		auto x = help[i];
		if (x.type == 1) {
			if (for_find.find(x.code) == for_find.end()) {
				num[x.code] = {0, id++};
				fhelp.push_back(num[x.code]);
				for_find.insert(x.code);
				fid[num[x.code].second] = x.code;
			}
		}
		if (x.type == 2) {
			for_find.erase(x.code);
		} 
		if (x.type == 3) {
			if (for_find.find(x.code) != for_find.end()) {
				num[x.code].first += x.plus;
				fhelp.push_back(num[x.code]);
			}
		}
	}


	sort(fhelp.begin(), fhelp.end(), cmp);

	/*cout << "fhelp = " << endl;
	for (auto i : fhelp) {
		cout << i.first << " " << i.second << endl;
	}
	cout << endl;	
*/

	for (int i = 0; i < fhelp.size(); i++) {
		find[i] = fhelp[i].second;
	}

/*	cout << "find = " << endl;
	for (auto i : find) {
		cout << i.first << " " << i.second << endl;
	}
	cout << endl;

	cout << endl;
*/	num.clear();
	for_find.clear();
	id = 0;
	for (int i = 0; i < q; i++) {
		auto x = help[i];
		if (x.type == 1) {
			if (for_find.find(x.code) == for_find.end()) {
				cout << "CREATED " << id << " 0\n";
				for_find.insert(x.code);
				num[x.code] = {0, id++};
				int pos = lower_bound(fhelp.begin(), fhelp.end(), num[x.code], cmp) - fhelp.begin();
			//	cout << "pos = " << pos << endl;
				upd(pos, 1);
			}
			else {
				cout << "EXISTS " << num[x.code].second << " " << num[x.code].first << '\n';
			}
		} 
		if (x.type == 2) {
			if (for_find.find(x.code) == for_find.end()) {
				cout << "BAD REQUEST\n"; 
			}
			else {
				cout << "OK " << num[x.code].second << " " << num[x.code].first << '\n';
				for_find.erase(x.code);
				int pos = lower_bound(fhelp.begin(), fhelp.end(), num[x.code], cmp) - fhelp.begin();
				upd(pos, 0);
			}
		}
		if (x.type == 3) {
			if (for_find.find(x.code) == for_find.end()) {
				cout << "BAD REQUEST\n";
			}
			else {
				int pos = lower_bound(fhelp.begin(), fhelp.end(), num[x.code], cmp) - fhelp.begin();
				upd(pos, 0);		
				num[x.code].first += x.plus;
				cout << "OK " << num[x.code].second << " " << num[x.code].first << '\n'; 
				pos = lower_bound(fhelp.begin(), fhelp.end(), num[x.code], cmp) - fhelp.begin();
				upd(pos, 1);
			}
		}
		if (x.type == 4) {
			if (for_find.size() == 0) {
				cout << "EMPTY\n";
			} 
			else {
				x.n++;
				x.n = min(x.n, (int) for_find.size());
				int ind = get(x.n);
			//	cout << "ind = " << ind << endl;
//				cout << "ind = " << ind << endl;	
				int i_d = find[ind];
				x.code = fid[i_d];
				cout << "OK " << x.code << " " << num[x.code].second << " " << num[x.code].first << '\n';
			}
		}


/*		cout << "num = " << endl;
		for (auto i : num) {
			cout << "code = " << i.first << endl;
		}
		cout << endl;*/

/*		cout << "tree = " << endl;
		for (int i = 0; i < fhelp.size(); i++)
			cout << tree[i] << " ";
		cout << endl;
		cout << endl;*/
	}
	return 0;
}