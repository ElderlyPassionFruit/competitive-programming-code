#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct cube{
    vector<int> a;
    cube() {
        a = {};
    }
};

bool operator<(const cube & a, const cube & b) {
    int cntA = 0;
    int cntB = 0;
    for (auto i : a.a) {
        for (auto j : b.a) {
            cntA += j < i;
            cntB += i < j;
        }
    }
    return cntA < cntB;
}

ld getP(const cube & a, const cube & b) {
    int cntA = 0;
    int cnt = 0;
    for (auto i : a.a) {
        for (auto j : b.a) {
            cntA += i < j;
            cnt++;
        }
    }
    assert(cnt);    
    return (ld) cntA / cnt;
}

mt19937 rnd(time(0));
const int CNT = 3;
const int SZ = 6;
const int BUBEN = 6;

ld getP(vector<cube> have) {
    ld ans = 1;
    for (int i = 0; i < CNT; i++) {
        chkmin(ans, getP(have[(i + 1) % CNT], have[i]));
    }
    return ans;
}

pair<ld, vector<cube>> ans = {-1, {}};

void out_ans(vector<cube> now) {
    //getP(now);
    //cout << "puhh" << endl;
    chkmax(ans, make_pair(getP(now), now));
    cout << "FIND!" << endl;
    for (auto i : now) {
        for (auto j : i.a) {
            cout << j << " ";
        }
        cout << endl;   
    }
    cout << endl;
}

vector<cube> All;

void genCube(cube now) {
    if (now.a.size() == SZ) {
        All.push_back(now);
        return;
    }
    if (now.a.empty()) {
        now.a.push_back(0);
    } else {
        now.a.push_back(now.a.back());
    }
    while (now.a.back() < BUBEN) {
        genCube(now);
        now.a[now.a.size() - 1]++;
    }
}

void genCubes() {
    //genCube({});
    vector<int> have(SZ * CNT);
    for (int i = 0; i < SZ; i++) {
        have[SZ * CNT - 1 - i] = 1;
    }
    do {
        cube now;
        for (int i = 0; i < SZ * CNT; i++) {
            if (have[i]) {
                now.a.push_back(i);
            }
        }
        All.push_back(now);
    } while (next_permutation(all(have)));
}

int IT = 0;

void gen(vector<cube> now, int pos) {
    IT++;
    if (IT % 1000 == 0) {
        cout << IT << endl;
    }
    if (pos == CNT) {
        if (now.back() < now[0]) {
            out_ans(now);
        } else {
        //    cout << "puhh" << endl;
        }
        return;
    } 
    for (auto i : All) {
        if (now.empty()) {
            gen({i}, pos + 1);
        } else {
            if (!(now.back() < i)) continue;
            bool ok = true;
            for (auto x : i.a) {
                for (auto my : now) {
                    for (auto y : my.a) {
                        ok &= x != y;
                        if (!ok) break;
                    }
                    if (!ok) break;
                }
                if (!ok) break;
            }
            if (!ok) continue;
            now.push_back(i);
            gen(now, pos + 1);
            now.pop_back();
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //genCubes();
    //cout << "GEN OK" << endl;
    cube a;
    a.a = {
1, 6, 7, 8, 12, 17 
};
  cube b;
    b.a = {
0, 4, 5, 14, 15, 16
};
    cout << (a < b) << " " << (b < a) << endl;
    //vector<int> order(All.size());
    //iota(all(order), 0);
    //shuffle(all(order), rnd);
    //while (order.size() > 3000) order.pop_back();
    //sort(all(order));
    //vector<cube> fall;
    //for (int i = 0; i < (int)All.size(); i++) {
    //    if (binary_search(all(order), i)) {
    //        fall.push_back(All[i]);
    //    }
    //}
    //All = fall;
    /*cout << "ALL.size() = " << All.size() << endl;
    gen({}, 0);
    cout << "ANS = " << endl;
    cout.precision(20);
    cout << ans.first << endl;
    for (auto i : ans.second) {
        for (auto j : i.a) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    return 0;
}


/*

2 3 9 10 11 13




 
1 3 3 3 3 6 = 19
36
*/