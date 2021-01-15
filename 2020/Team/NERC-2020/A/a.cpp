#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

//const int N = 400;
//bool dp[N][N];

bool flag = true;
vector<vector<int>> ans;

void gen(int a, int b) {
    //cout << "a = " << a << " b = " << b << endl;
    if (a == 1 && b == 0) {
        ans.push_back({1, 0, 0});
    } else if (a == 0 && b == 1) {
        ans.push_back({2, 0, 0});
    } else if (a % 2 == 1 && b % 2 == 0) {
        ans.push_back({1, 0, 0});
        int aL = a / 2;
        int aR = a / 2;
        int bL = b / 2;
        int bR = b / 2;
        int ind = ans.size() - 1;
        if (aL + bL > 0) {
            ans[ind][1] = ans.size() + 1;
            gen(aL, bL);
        }
        if (aR + bR > 0) {
            ans[ind][2] = ans.size() + 1;
            gen(aR, bR);
        }
    } else if (a % 2 == 0 && b % 2 == 1) {
        ans.push_back({2, 0, 0});
        int aL = a / 2;
        int aR = a / 2;
        int bL = b / 2;
        int bR = b / 2;
        int ind = ans.size() - 1;
        if (aL + bL > 0) {
            ans[ind][1] = ans.size() + 1;
            gen(aL, bL);
        }
        if (aR + bR > 0) {
            ans[ind][2] = ans.size() + 1;
            gen(aR, bR);
        }
    } else if (a % 2 == 0 && b % 2 == 0) {
        if (a == 0) {
            flag = false;
            return;
        }
        ans.push_back({1, 0, 0});
        int aL = a / 2;
        int aR = a - aL - 1;
        int bL = b / 2;
        int bR = b / 2;
        int ind = ans.size() - 1;
        if (aL + bL > 0) {
            ans[ind][1] = ans.size() + 1;
            gen(aL, bL);
        }
        if (aR + bR > 0) {
            ans[ind][2] = ans.size() + 1;
            gen(aR, bR);
        } 
    } else if (a % 2 == 1 && b % 2 == 1) {
        ans.push_back({2, 0, 0});
        int aL = a / 2;
        int aR = a - aL;
        int bL = b / 2;
        int bR = b / 2;
        int ind = ans.size() - 1;
        if (aL + bL > 0) {
            ans[ind][1] = ans.size() + 1;
            gen(aL, bL);
        }
        if (aR + bR > 0) {
            ans[ind][2] = ans.size() + 1;
            gen(aR, bR);
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    /*dp[0][0] = 1;
    for (int a = 0; a < N; ++a) {
        for (int b = 0; b < N; ++b) {
            if (dp[a][b]) continue;
            bool ok = false;
            if (a % 2 == 1 || b % 2 == 1) ok = true;
            for (int type = 0; type <= 1; ++type) {
                if (type == 0 && a == 0) continue;
                if (type == 1 && b == 0) continue;
                for (int aL = 0; aL <= a - (type == 0); ++aL) {
                    for (int bL = 0; bL <= b - (type == 1); ++bL) {
                        if (!dp[aL][bL]) continue;
                        int aR = a - aL - (type == 0);
                        int bR = b - bL - (type == 1);
                        if (aL > aR) continue;
                        if (!dp[aR][bR]) continue;
                        if (abs(aL + bL * 2 - aR - bR * 2) > 1) continue;
                        dp[a][b] = 1;
                        if (a % 2 == 0 && b % 2 == 0) {
                            if (type == 0) {
                                ok = true;
                            }
                            //cout << a << " " << b << " " << aL << " " << bL << " " << aR << " " << bR << " root = " << type << endl;
                        }
                    }
                }
            } 
            if (!ok && dp[a][b]) {
                //cout << "a = " << a << " b = " << b << endl;
                assert(false);
            }
        }
    }*/
    /*for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << dp[i][j] << " "; 
        }
        cout << endl;
    }*/
    /*for (int a = 0; a < N; ++a) {
        for (int b = 0; b < N; ++b) {
            if (!a && !b) continue;
        }
    }*/
    int a, b;
    cin >> a >> b;
    ans.clear();
    flag = true;
    gen(a, b);
    //assert(flag == dp[a][b]);
    
    if (flag) {
        for (auto i : ans) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "-1\n";
    }

	return 0;
}