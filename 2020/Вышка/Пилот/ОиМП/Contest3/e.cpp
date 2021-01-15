#include <iostream>
#include <vector>

template <typename InIter, typename OutIter>
OutIter reverse_copy(InIter first, InIter last, OutIter out) {
    if (first == last) {
        return out;
    }
    do {
        --last;
        *out = *last;
        ++out;
    } while (first != last);
    return out;
}

using namespace std;

signed main() {
    vector<int> v = {1, 2, 3};
    vector<int> ans;
    reverse_copy(v.begin(), v.end(), inserter(ans, ans.begin()));
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}