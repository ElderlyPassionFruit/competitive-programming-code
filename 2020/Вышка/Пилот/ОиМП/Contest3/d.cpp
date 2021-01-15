#include <iostream>
#include <vector>

template <typename InIter1, typename InIter2, typename OutIter>
OutIter set_difference(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2, OutIter out) {
    while (first1 != last1 && first2 != last2) {
        if ((*first1) < (*first2)) {
            *out = *first1;
            ++first1;
            ++out;
        } else if ((*first1) > (*first2)) {
            ++first2;
        } else {
            ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
    return out;
}

using namespace std;

signed main() {
    vector<int> a = {1, 2, 5, 5, 5, 9};
    vector<int> b = {1, 2, 3};
    vector<int> ans;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(ans, ans.begin()));
    for (auto i : ans) {
        cout << i << " ";
    } 
    cout << endl;
    return 0;
}