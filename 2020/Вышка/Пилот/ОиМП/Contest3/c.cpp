#include <iostream>
#include <vector>

template <typename Iter>
Iter unique(Iter first, Iter last) {
    Iter answerEnd = first;
    if (first == last) {
        return answerEnd;
    }
    ++first;
    for (; first != last; ++first) {
        if (*answerEnd != *first) {
            ++answerEnd;
            *answerEnd = *first;
        }
    }
    return ++answerEnd;
}

using namespace std;


signed main() {
    vector<int> v = {1,2,1,1,3,3,3,4,5,4};
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}