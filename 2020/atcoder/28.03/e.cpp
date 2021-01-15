#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int x, y, a, b, c;
vector<int> p, q, r;
void read() {
	cin >> x >> y >> a >> b >> c;
	p.resize(a);
	for (auto &i : p)
		cin >> i;
	sort(all(p));
	reverse(all(p));
	q.resize(b);
	for (auto &i : q)
		cin >> i;
	sort(all(q));
	reverse(all(q));
	r.resize(c);
	for (auto &i : r)
		cin >> i;
	sort(all(r));
	reverse(all(r));
}

priority_queue<int> B, C;

void wr(priority_queue<int> a) {
	while (!a.empty()) {
		cout << a.top() << " ";
		a.pop();
	}
	cout << endl;
}

int ans = 0;

void run() {
	int min_A = max(0LL, x - c);
	int fans = 0;
	for (int i = 0; i < min_A; i++)
		fans += p[i];
	for (int i = 0; i < x - min_A; i++) {
		C.push(-r[i]);
		fans += r[i];
	}
	//cout << "puhh" << endl;
	//cout << "min_A = " << min_A << endl;
	//wr(C);
	//cout << endl;
	for (int i = 0; i < y; i++) {
		if (B.size() < y && C.size() < r.size()) {
			int valQ = q[B.size()];
			int valR = r[C.size()];
			if (valQ < valR) {
				C.push(-valR);
				fans += valR;
			} else {
				B.push(-valQ);
				fans += valQ;
			}
		} else if (B.size() < y) {
			fans += q[B.size()];
			B.push(-q[B.size()]);
		} else {
			assert(C.size() < r.size());
			fans += r[C.size()];
			C.push(-r[C.size()]);
		}
	}
	//cout << "puhh" << endl;
	//wr(B);
	//wr(C);
	//cout << endl;
	chkmax(ans, fans);
	for (int i = min_A; i < x; i++) {
		fans += p[i];
		if (!B.empty() && (int)C.size() + i >= x) {
			int valB = -B.top();
			int valC = -C.top();
			if (valB < valC) {
				fans -= valB;
				B.pop();
			} else {
				fans -= valC;
				C.pop();
			}
		} else if (!B.empty()) {
			fans -= -B.top();
			B.pop();
		} else {
			assert((int)C.size() + i >= x);
			fans -= -C.top();
			C.pop();
		}
		/*(if (fans == 14) {
			cout << "out = " << endl; 
			cout << i << endl;
			wr(B);
			wr(C);
			exit(0);
		}*/
		chkmax(ans, fans);
	}
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