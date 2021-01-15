#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <set>
#include <map>
#define ll long long
#define ld long double

using namespace std;

int dist(string& a, string& b) {
    int x = 0;
    for (int i = 0; i < 8; ++i) {
        if (a[i] == b[i])
            x++;
    }
    return x;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> mat(n);
    for (int i = 0; i < n; ++i) {
        cin >> mat[i];
    }
    //reverse(mat.begin(), mat.end());
    vector<int> ans(n);
    ans[0] = 0;
    for (int i = 1; i < n; ++i) {
        ans[i] = 0;
        for (int j = 1; j <= 8; ++j) {
            int i2 = i - j;
            if (i2 < 0)
                break;
            if (j <= dist(mat[i2], mat[i])) {
                if (ans[i2] == 0)
                    ans[i] = 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << 2 - ans[i];
    }
}
//*/