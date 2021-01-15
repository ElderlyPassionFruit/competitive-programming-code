#include <bits/stdc++.h>
 
using namespace std;
#define int long long
 

string north = "move north", east = "move east", south = "move south", west = "move west";
vector <string> MOVE = {north, east, south, south, west, west, north, north, east, south};

string help = "echo help";

bool check(string s) {
    cout << s << endl;
    string x;
    cin >> x;
    return x == "found" || x == "win";
}
 
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int cnt = 0;
    while (true) {
        bool flag = check(MOVE[cnt++]);
        if (flag)
            break;
    }
 	if (cnt > 8)
 		return 0;

 	if (cnt == 1) {
 		check(south);
 		for (int i = 0; i < 7; i++) {
 			check(help);
 		}
 		check(north);
 	}

 	if (cnt == 2) {
 		check(west);
 		for (int i = 0; i < 6; i++) {
 			check(help);
 		}
 		check(east);
 	}

 	if (cnt == 3) {
 		check(north);
 		for (int i = 0; i < 5; i++) {
 			check(help);
 		}
 		check(south);
 	}

 	if (cnt == 4) {
 		check(north);
 		for (int i = 0; i < 4; i++) {
 			check(help);
 		}
 		check(south);
 	}

 	if (cnt == 5) {
 		check(north);
 		for (int i = 0; i < 3; i++) {
 			check(help);
 		}
 		check(south);
 	}

 	if (cnt == 6) {
 		check(north);
 		for (int i = 0; i < 2; i++) {
 			check(help);
 		}
 		check(south);
 	}

 	if (cnt == 7) {
 		check(north);
 		check(help);
 		check(south);
 	}

 	if (cnt == 8) {
 		check(south);
 		check(north);
 	}
    return 0;
}