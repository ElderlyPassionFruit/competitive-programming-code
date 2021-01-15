#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

namespace perc_st{
	struct event{
		int pos, val;
	};

	vector<event> st(1);

	void push(int last, int val) {
		st.resize(st.size() + 1);
		st[st.size() - 1].val = val;
		st[st.size() - 1].pos = last;
	}

	int pop(int last) {
		auto k = st[st[last].pos];
		push(k.pos, k.val);
		return st[last].val;
	}

	void wr() {
		cout << "st = " << endl;
		for (auto i : st)
			cout << i.pos << " " << i.val << endl;
		cout << endl;
	}
};

int n;
void read() {
	cin >> n;
}

vector<int> ans;

void run() {
	for (int i = 0; i < n; i++) {
		int t, type;
		cin >> t >> type;
		if (type == 0) {
			ans.push_back(perc_st::pop(t));
		}
		else {
			perc_st::push(t, type);
		}
		//perc_st::wr();
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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