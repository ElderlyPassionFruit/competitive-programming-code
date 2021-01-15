#include <bits/stdc++.h>

using namespace std;
#define int long long

int get(char x) {
    if (x == '(') return 1;
    if (x == ')') return -1;
    if (x == '[') return 2;
    if (x == ']') return -2;
    if (x == '{') return 3;
    if (x == '}') return -3;
    if (x == '<') return 4;
    if (x == '>') return -4;
    assert(false);
    return 0;
}

signed main() {
    string s;
    cin >> s;
    vector<char> st;
    for (auto i : s) {
        int now = get(i);
        if (now > 0) {
            st.push_back(now);
        } else {
            if (st.empty() || st.back() != abs(now)) {
                cout << "NO\n";
                return 0;
            }
            st.pop_back();
        }
    }    
    if (st.empty()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}