#include <bits/stdc++.h>

using namespace std;
#define int long long
const int itreations = 1e6;
void read() {
	string ans1;
	string ans2;
	cin >> ans1 >> ans2;

	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < itreations; i++) {
		string have = "000";
		while (true) {
			int a = rand() % 2;
			if (a == 0)
				have += 'O';
			else
				have += 'P';
			string check = "";
			check += have[have.size() - 3];
			check += have[have.size() - 2];
			check += have[have.size() - 1];
			if (check == ans1) {
				cnt1++;
				break;
			}
			if (check == ans2) {
				cnt2++;
				break;
			}
		}
	}
	cout.precision(20);
	cout << 1.0 * cnt1 / (cnt1 + cnt2) << " " << 1.0 * cnt2 / (cnt1 + cnt2) << endl;
}

void run() {

}

void write() {

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