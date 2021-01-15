#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;

void read() {
    cin >> s;
}

const int N = 1010;
const int LOG = 10;
int cnt[LOG];
int pows[N];
int pref[N];
string ans;

int getMod(vector<int>& nums) {
    int ans = 0;
    for (auto i : nums) {
        ans = (ans * 10 + i) % 7;
    }
    return ans;
}

bool stupidCheck(int mod) {
    vector<int> nums;
    for (int i = 0; i < LOG; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            nums.push_back(i);
        }
    } 
    sort(all(nums));
    do {
        if (getMod(nums) == mod) {
            return true;
        }
    } while (next_permutation(all(nums)));
    return false;
}

int get(int pos, int num1, int num2, int cnt2) {
    int ans = (pref[cnt2] * num2) % 7;
    ans = (ans - pows[pos] * num2 + pows[pos] * num1) % 7;
    ans = (ans + 7) % 7;
    return ans;
}

bool check(int mod, int num1, int num2, int cnt2) {
    for (int pos = 0; pos <= cnt2; ++pos) {
        if (get(pos, num1, num2, cnt2) == mod) {
            return true;
        }
    }
    return false;
}

int myCnt[7];

bool check(int mod, int pos) {
    mod = (7 - mod) % 7;
    //cout << "mod = " << mod << " pos = " << pos << endl;
    if (pos <= 6) {
        return stupidCheck(mod);
    }

    fill(myCnt, myCnt + 7, 0);
    for (int i = 0; i < LOG; ++i) {
        myCnt[i % 7] += cnt[i];
    }
    int cntDiff = 0;
    for (int i = 0; i < 7; ++i) {
        if (myCnt[i]) {
            cntDiff++;
        }
    }
    if (cntDiff >= 3) {
        return true;
    } else if (cntDiff == 1) {
        int num = -1;
        for (int i = 0; i < 7; ++i) {
            if (myCnt[i]) {
                num = i;
                break;
            }
        }    
        assert(num != -1);
        int ans = 0;
        for (int i = 0; i < pos; ++i) {
            ans = (ans * 10 + num) % 7;
        }
        return ans == mod;
    } else {
        assert(cntDiff == 2);
        int num1 = -1, num2 = -1;
        for (int i = 0; i < 7; ++i) {
            if (!myCnt[i]) continue;
            if (num1 == -1) {
                num1 = i;
            } else {
                num2 = i;
            }
        }
        assert(num1 != -1 && num2 != -1);
        if (myCnt[num1] > 1 && myCnt[num2] > 1) {
            return true;
        } else {
            if (myCnt[num1] > myCnt[num2]) {
                swap(num1, num2);
            }
            assert(myCnt[num1] == 1);
            return check(mod, num1, num2, myCnt[num2]);
        }
    }
}

int getNum(int mod, int pos) {
    //cout << "getNum = " << mod << " " << pos << endl;
    for (int num = 9; num >= 0; --num) {
        if (!cnt[num]) continue;
        //cout << "fcheck num = " << num << endl;
        --cnt[num];
        mod = (mod + pows[pos] * num) % 7;
        //cout << "mod = " << mod << endl;
        if (check(mod, pos)) {
            return num;
        }
        mod = (mod - pows[pos] * num) % 7;
        mod = (mod + 7) % 7;
        ++cnt[num];
    }
    return -1;
}

void solve() {
    ans = "";
    int mod = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        int num = getNum(mod, i);
        //cout << "num = " << num << endl;
        if (num == -1) {
            cout << "-1\n";
            exit(0);
        }
        if (i == (int)s.size() - 1 && num == 0) {
            cout << "-1\n";
            exit(0);
        }
        ans += '0' + num;
        mod = (mod + pows[i] * num) % 7;
    } 
}

void init() {
    fill(cnt, cnt + LOG, 0);
    for (auto i : s) {
        ++cnt[i - '0'];
    }
    pows[0] = 1;
    pref[0] = 1;
    for (int i = 1; i < N; ++i) {
        pows[i] = (pows[i - 1] * 10) % 7;
        pref[i] = (pref[i - 1] + pows[i]) % 7;
    }
    /*cout << "cnt = " << endl;
    for (int i = 0; i < LOG; ++i) {
        cout << cnt[i] << " ";
    }
    cout << endl;
    cout << "pows = " << endl;
    for (int i = 0; i < LOG; ++i) {
        cout << pows[i] << " ";
    }
    cout << endl;
    cout << "pref = " << endl;
    for (int i = 0; i < LOG; ++i) {
        cout << pref[i] << " ";
    }
    cout << endl;*/
}

void run() {
    init();
    solve();
}

void write() {
    cout << ans << endl;
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