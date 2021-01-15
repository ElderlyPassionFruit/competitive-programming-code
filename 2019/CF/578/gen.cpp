#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const ll mod = 1000000021;
ll b = 239;

map<int,string> mp;

int main() {
	while (true) {
		string s = "";
		ll h = 0;
		for(int i = 0; i < 10; i++) {
			int x = rand() % 26;
			h = (h * b + (x + 65)) % mod;
			s = s + (char)(x + 65);
		}	
		if (mp.count(h)) {
			reverse(mp[h].begin(), mp[h].end());
			reverse(s.begin(), s.end());
			cout << 2 << endl << mp[h] << " " << s << endl;
			return 0;
		}
		mp[h] = s;
	}		
}
