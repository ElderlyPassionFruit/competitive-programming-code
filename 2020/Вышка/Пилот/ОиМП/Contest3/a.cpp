

#include <bits/stdc++.h>

template <typename It, typename Pred>
bool any_of(It first, It last, Pred f) {
    for (; first != last; ++first) {
        if (f(*first)) {
            return true;
        }
    }
    return false;
}

using namespace std;

bool check(int x) {
    return x >= 4;
}

signed main() {
    vector<int> v(3);
    iota(v.begin(), v.end(), 0);
    cout << myAny_of(v.begin(), v.end(), check) << endl;
    return 0;
}