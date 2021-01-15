#include <iostream>
#include <vector>

template <typename InIter, typename OutIter, typename Predicate>
OutIter remove_copy_if(InIter first, InIter last, OutIter out, Predicate f) {
    for (; first != last; ++first) {
        if (!f(*first)) {
            *out = *first;
            ++out;
        }
    }
    return out;
}

using namespace std;

bool check(int x) {
    return x & 1;
}

signed main() {
    vector<int> v(5);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i;
    }
    vector<int> a;
    a.resize(remove_copy_if(v.begin(), v.end(), a.begin(), check) - a.begin());
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}