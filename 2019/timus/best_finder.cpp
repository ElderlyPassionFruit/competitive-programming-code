//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

//const int CNT = 1;
//const int SZ = 1;
int CNT, SZ;
int FULL;
//const int FULL = SZ * CNT;
const int MAXN = 2e5;
int topAll = 0;
vector<int> All[MAXN];
vector<int> nxt[MAXN];

inline bool checkLose(int a, int b) {
    int cntA = 0;
    //int cntB = 0;
    int pos;
    pos = 0;
    for (int i = 0; i < SZ; ++i) {
        while (pos < SZ && All[a][i] > All[b][pos]) ++pos;
        cntA += pos;
    }
    /*pos = 0;
    for (int i = 0; i < SZ; ++i) {
        while (pos < SZ && All[b][i] > All[a][pos]) ++pos;
        cntB += pos;
    }*/
    return cntA * 2 < SZ * SZ;
}

inline bool checkEqual(int a, int b) {
    int pos = 0;
    for (int i = 0; i < SZ; ++i) {
        while (pos < SZ && All[a][i] > All[b][pos]) ++pos;
        if (pos < SZ && All[a][i] == All[b][pos]) return true;
    }
    return false;
}

inline bool checkLess(int a, int b) {
    return All[a] < All[b];
}

inline bool check(int a, int b) {
    //if (checkLess(a, b)) return false;
    if (checkEqual(a, b)) return false;
    if (!checkLose(a, b)) return false;
    return true;
}

inline void genCubes() {
    vector<int> have(FULL);
    for (int i = 0; i < SZ; ++i) {
        have[SZ * CNT - 1 - i] = 1;
    }
    do {
        vector<int> now;
        for (int i = 0; i < FULL; ++i) {
            if (have[i]) {
                now.push_back(i);
            }
        }
        All[topAll++] = now;
    } while (next_permutation(all(have)));
    cerr << "topAll = " << topAll << endl;
    sort(All, All + topAll);
    for (int i = 0; i < topAll; ++i) {
        for (int j = 0; j < topAll; ++j) {
            if (check(i, j)) {
                nxt[i].push_back(j);
            }
        }
    }
}

inline ld getP(int a, int b) {
    int cntA = 0;
    int pos = 0;
    for (int i = 0; i < SZ; ++i) {
        while (pos < SZ && All[a][i] > All[b][pos]) pos++;
        cntA += pos;
    }
    return (ld) cntA / (SZ * SZ);
}

vector<int> now;
int pos;

inline ld getP() {
    ld ans = 1;
    for (int i = 0; i < CNT; ++i) {
        ld fans = 0;
        for (int j = 0; j < CNT; j++) {
            chkmax(fans, getP(now[i], now[j]));
        }
        chkmin(ans, fans);
    //    chkmin(ans, getP(now[(i + 1) % CNT], now[i]));
    }
    return ans;
}

ld ans = -1;
vector<int> fout;

inline void write() {
    for (int i = 0; i < CNT; ++i) {
        for (auto j : All[now[i]]) {
            cout << j << " ";
        }
        cout << endl;   
    }
} 

ll cnt = 0;
ll cnt2 = 0;
inline void write_cerr() {
    for (int i = 0; i < CNT; ++i) {
        for (auto j : All[fout[i]]) {
            cerr << j << " ";
        }
        cerr << endl;   
    }  
}

inline void out_ans() {
    ld have = getP();
    if (have > ans) {
        ans = have;
        for (int i = 0; i < pos; ++i) {
            fout[i] = now[i];
        }
        cerr << "new best ans!" << endl;
        cerr << "p = " << ans << endl;
        write_cerr();
    }
    cnt++;
    cnt2++;
    if (cnt2 == 10000) {
        cnt2 = 0;
        cerr << "FIND! " << cnt  << endl;
    }
}

ll IT = 0;
ll IT2 = 0;

vector<bool> used;
vector<int> have;

void gen() {
    IT++;
    IT2++;
    if (IT2 == 1000000) {
        cerr << "it = " << IT << " best_p = " << ans << endl;
        IT2 = 0;
        cerr << "ans = " << endl;
        write_cerr();
    }

    if (pos == CNT - 1) {
        //memset(used, 0, sizeof used);
        fill(all(used), 0);
        for (int i = 0; i < pos; ++i) {
            for (auto j : All[now[i]]) {
                used[j] = true;
            }
        }
        int ptr = 0;
        for (int i = 0; i < FULL; ++i) {
            if (!used[i]) {
                have[ptr++] = i;
            }
        }
        int posHave = lower_bound(All, All + topAll, have) - All;
        if (checkLose(now[pos - 1], posHave) && checkLose(posHave, now[0])) {
            now[pos++] = posHave;
            out_ans();
            pos--;
        }
        return;
    }
    if (pos == 0) {
        for (int i = 0; i < topAll; ++i) {
            now[pos++] = i;
            gen();
            pos--;
        }
    } else {
        for (auto i : nxt[now[pos - 1]]) {
            bool ok = true;
            for (int j = 0; j + 1 < pos; ++j) {
                if (checkEqual(now[j], i) || checkLess(now[j], i)) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            now[pos++] = i;
            gen();
            pos--;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cerr.precision(20);
    cout.precision(20);
    cin >> CNT >> SZ;
    now.resize(CNT);
    fout.resize(CNT);
    have.resize(SZ);
    FULL = CNT * SZ;
    used.resize(FULL);
    genCubes();
    cerr << "GEN OK" << endl;
    gen();
    cout << "CNT = " << CNT << " SZ = " << SZ << endl;
    cout << "FULL IT = " << IT << endl;
    cout << "FULL cnt = " << cnt << endl;
    cout << "ANS = " << endl;
    cout << ans << endl;
    for (int i = 0; i < CNT; ++i) {
        for (auto j : All[fout[i]]) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}
