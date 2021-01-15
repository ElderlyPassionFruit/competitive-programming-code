#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <set>
#include <map>
#define ll long long
#define ld long double

using namespace std;

ll ans = -1;

void gen(int need, ll now,  vector<int> &coun) {
    if (need == 0) {
        if (now % 7 == 0) {
            ans = max(ans, now);
        }
        return;
    }
    for (int i = 0; i <= 9; ++i) {
        if (coun[i] == 0) {
            continue;
        }
        if (i == 0 && now == 0) {
            continue;
        }
        coun[i] -= 1;
        gen(need - 1, now * 10 + i, coun);
        coun[i] += 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    string s;
    cin >> s;
    vector<int> coun(10);
    for (int i = 0; i < s.size(); ++i) {
        coun[s[i] - '0']++;
    }
    gen(s.size(), 0, coun);
    cout << ans << "\n";
}
//*/