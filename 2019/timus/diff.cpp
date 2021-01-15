#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));
const int CNT = 3;
const int SZ = 6;
const int BUBEN = 6;

typedef ll cube;

int get(ll mask) {
    return __builtin_popcountll(mask);
}

bool check(cube a, cube b) {
    int cntA = 0;
    int cntB = 0;
    for (int bit = 1; bit < CNT * SZ; bit++) {
        if ((a >> bit) & 1) {
            cntA += get(((1LL << (bit - 1)) - 1) & b); 
        }
        if ((b >> bit) & 1) {
            cntB += get(((1LL << (bit - 1)) - 1) & a); 
        }
    }
    return cntA < cntB;
}

ld getP(cube a, cube b) {
    int cntA = 0;
    for (int bit = 1; bit < CNT * SZ; bit++) {
        if ((a >> bit) & 1) {
            cntA += get(((1LL << (bit - 1)) - 1) & b); 
        }
    }
    return (ld) cntA / (SZ * SZ);
}

ld getP(vector<cube> have) {
    ld ans = 1;
    for (int i = 0; i < CNT; i++) {
        chkmin(ans, getP(have[(i + 1) % CNT], have[i]));
    }
    return ans;
}

pair<ld, vector<cube>> ans = {-1, {}};

vector<int> getVal(ll mask) {
    vector<int> ans;
    for (int bit = 0; bit < (SZ * CNT); bit++) {
        if ((mask >> bit) & 1) {
            ans.push_back(bit);
        }
    }
    return ans;
}

void write(vector<cube> now) {
    for (auto i : now) {
        auto have = getVal(i);
        for (auto j : have) {
            cout << j << " ";
        }
        cout << endl;   
    }
}

void out_ans(vector<cube> now) {
    ld fans = getP(now);
    if (fans > ans.first) {
        ans = make_pair(fans, now);
    }
    cout << "FIND!" << endl;
    write(now);
    cout << endl;
}

vector<cube> All;

void gencubes() {
    vector<int> have(SZ * CNT);
    for (int i = 0; i < SZ; i++) {
        have[SZ * CNT - 1 - i] = 1;
    }
    do {
        cube now;
        for (int i = 0; i < SZ * CNT; i++) {
            if (have[i]) {
                now |= 1LL << i;
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
        IT++;
        cout << IT << endl;
        if (check(now.back(), now[0])) {
            out_ans(now);
        } else {
            cout << "FAIL!" << endl;
            write(now);
            assert(false);
        }
        return;
    } 
    for (auto i : All) {
        if (now.empty()) {
            gen({i}, pos + 1);
        } else {
            if (!check(now.back(), i)) continue;
            bool ok = true;
            for (auto my : now) {
                ok &= ((i & my) == 0);
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
    gencubes();
    cout << "GEN OK" << endl;
    cout << "ALL.size() = " << All.size() << endl;
    gen({}, 0);
    cout << "ANS = " << endl;
    cout.precision(20);
    cout << ans.first << endl;
    write(ans.second);
    return 0;
}