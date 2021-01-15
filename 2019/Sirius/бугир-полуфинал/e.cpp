#include <bits/stdc++.h>

using namespace std;
#define int long long

const string INF = "1000000000000000000";

string SORT(map <char, int> x) {
	string ans = "";
	for (auto i : x) {
		if (i.first != '0' && i.second != 0) {
			ans += i.first;
			x[i.first]--;
			break;
		}
	}
	if (ans == "")
		return "-1";

	for (int i = 0; i < x['0']; i++)
		ans += "0";
	
	x['0'] = 0;

	for (auto i : x) {
		for (int j = 0; j < i.second; j++) {
			ans += i.first;
		}
	} 
	return ans;
}

bool check1(map <char, int> x) {
	if (x['0'] == 0) {
		return false;
	}
	x['0']--;
	string fans = SORT(x);
	if (fans == "-1") {
		return false;
	}
	if (fans.size() > 18 && fans != INF)
		return false;
	return true;
}

bool check2(map <char, int> x) {
	if (x['0'] < 18 || x['1'] < 1)
		return false;
	x['0'] -= 18;
	x['1'] -= 1;
	string fans = SORT(x);
	if (fans == "-1")
		return false;
	if (fans.size() > 18 && fans != INF)
		return false;
	return true;
}

bool check3(map <char, int> x) {
	int cnt = 0;
	for (auto i : x)
		cnt += i.second;
	if (cnt > 19)
		return false;

	string ans = "";
	for (auto i : x) {
		if (i.first != '0' && i.second != 0) {
			ans += i.first;
			x[i.first]--;
			break;
		}
	}

	if (ans == "")
		return false;

	string fans = SORT(x);

	if (fans == "-1")
		return false;

	return true;
}

bool check4(map <char, int> x) {
	int cnt = 0;
	for (auto i : x)
		cnt += i.second;
	if (cnt <= 19)
		return false;

	string fans = SORT(x);
	if (fans == "-1")
		return false;

	int n = fans.size();

	string fans1 = "";
	for (int i = 0; i < n - 18; i++){
		fans1 += fans[i];
		x[fans[i]]--;
	}
	
	fans = SORT(x);
	if (fans == "-1")
		return false;
	if (fans1.size() > 18)
		return false;
	
	return true;
}

string s;	
map <char, int> x;

void read() {
	cin >> s;
	if (s.size() == 1) {
		cout << "-1 -1" << endl;
		exit(0);
	}

	if (s == "00") {
		cout << "0 0" << endl;
		exit(0);
	}

	for (auto i : s) {
		x[i]++;
	}
}

void run() {
	if (check1(x)) {
		x['0']--;
		string ans = SORT(x);
		cout << "0 " << ans << endl;
		exit(0);
	}

	if (check2(x)) {
		x['0'] -= 18;
		x['1']--;
		string ans = SORT(x);
		cout << ans << " " << INF << endl;
		exit(0);
	}

	if (check3(x)) {
		string ans = "";
		for (auto i : x) {
			if (i.first != '0' && i.second != 0) {
				ans += i.first;
				x[i.first]--;
				break;
			}
		}
		cout << ans << " ";
		ans = SORT(x);
		cout << ans << endl;
		exit(0);
	}

	if (check4(x)) {
		string fans = SORT(x);
		int n = fans.size();
		string fans1 = "";
		for (int i = 0; i < n - 18; i++){
			fans1 += fans[i];
			x[fans[i]]--;
		}
		fans = SORT(x);
		cout << fans1 << " " << fans << endl;
		exit(0);
	}
	cout << "-1 -1" << endl;
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