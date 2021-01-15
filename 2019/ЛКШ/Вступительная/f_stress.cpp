//#include "stdafx.h"
#pragma GCC optimize("O3")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#include <stdlib.h>
#include<iostream>
 
#include<vector>
#include<deque>
#include<queue>
#include<bitset>
#include<list>
#include<stack>
 
#include<string>
#include<algorithm>
#include<cmath>
#include<complex>
#include<functional>
#include <utility>
 
#include <omp.h>
#include<ctime>
#include <map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<cstdio>
 
#include <fstream>
#include<sstream>
#include<limits.h>
#include<assert.h>
#define int long long
using namespace std;
#pragma Gcc optimize("O3")
#pragma Gcc target("sse,sse2,sse3,ssse3,sse4,popc2nt,abm,mmx,avx,tune=native")
#pragma Gcc optimize("unroll-loops")
#define fastio() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int Euler_funktion(int n) {
    int res = n;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n%i == 0) {
            res -= i;
            n /= i;
            i--;
        }
    }
    return res;
}
int speed_power(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            res *= a;
            n--;
        }
        else {
            res *= res;
            n /= 2;
        }
    }
    return res;
}
int mod_speed_power(int a, int n, int mod) {
    int res = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            res *= a;
            n--;
        }
        else {
            res *= res;
            n /= 2;
        }
        res %= mod;
    }
    return res;
}
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a > 0 && b > 0) {
        if (a > b) {
            a %= b;
        }
        else {
            b %= a;
        }
    }
    return a + b;
}
int lcm(int a, int b) {
    a = abs(a);
    b = abs(b);
    return a * b / gcd(a, b);
}
pair<pair<int, int>, int> full_gcd2(int a, int b) {
    if (a == 0) {
        return { {0,1},b };
    }
    auto res = full_gcd2(max(a, b) % min(a, b), min(a, b));
    return { {res.first.second - (b / a)*res.first.first,res.first.first}, res.second };
}
pair<pair<int, int>, int> full_gcd(int a, int b, int c) {
    if (c%gcd(a, b) != 0) {
        return { {-1,-1},-1 };
    }
    c /= gcd(a, b);
    auto res = full_gcd2(min(abs(a), abs(b)), max(abs(a), abs(b)));
    if (abs(a) > abs(b)) {
        swap(res.first.first, res.first.second);
    }
    if (a < 0) {
        res.first.first *= (-1);
    }
    if (b < 0) {
        res.first.second *= (-1);
    }
    return { {res.first.first*c,res.first.second*c},res.second };
}
int field[1000][1000];
void uberi(int a, int b) {
    if (field[a][b] == 0) {
        return;
    }
    while (field[a][b + 1] == 1 || field[a + 1][b] == 1) {
        if (field[a][b + 1] == 1) {
            uberi(a, b + 1);
        }
        if (field[a + 1][b] == 1) {
            uberi(a + 1, b);
        }
    }
    field[a][b] = 0;
    field[a][b + 1] = 1;
    field[a + 1][b] = 1;
    cout << a << " " << b;
    cout << endl;
}
map<int, long long>map1;
vector<int>vec, vec2;
signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fastio();
    int a, b, c = 0, d = 0;
    string s;
    cin >> a;
    for (int i = 0; i < a; i++) {
        cin >> b;
        vec.push_back(b);
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i < vec.size(); i++) {
        vec2.push_back((vec[i] - vec[i - 1]) * 10);
    }
    int l = 0, r = 3e10;
    while (r - l > 1) {
        int res = (r + l) / 2;
        int l2 = 0, r2 = a + 1;
        while (r2 - l2 > 1) {
            int res2 = (r2 + l2) / 2;
            int res3 = res-10;
            int res4 = res-10;
            int check = 0;
            for (int i = res2 - 1; i < vec2.size(); i++) {
                res4 -= vec2[i];
                if (res4 < 0) {
                    res3-=10;
                    res4 = res3;
                    res4 -= vec2[i];
                    if (res4 < 0) {
                        check = 1;
                        break;
                    }
                }
            }
            if (check == 0) {
                r2 = res2;
            }
            else {
                l2 = res2;
            }
        }
        int l3 = 0, r3 = a - 1;
        while (r3 - l3 > 1) {
            int res2 = (r3 + l3) / 2;
            int res3 = res-10;
            int res4 = res-10;
            int check = 0;
            for (int i = res2 - 1; i >= 0; i--) {
                res4 -= vec2[i];
                if (res4 < 0) {
                    res3-=10;
                    res4 = res3;
                    res4 -= vec2[i];
                    if (res4 < 0) {
                        check = 1;
                        break;
                    }
                }
            }
            if (check == 0) {
                l3 = res2;
            }
            else {
                r3 = res2;
            }
        }
        int res2 = 0;
        r2--;
        for (int i = l3; i < r2; i++) {
            res2 += vec2[i];
        }
        if (res2 <= res * 2) {
            r = res;
        }
        else {
            l = res;
        }
    }
    cout << r / 10 << "." << r % 10 << endl;
    return 0;
}