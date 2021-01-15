#include <cstddef>

template<typename Iterator1, typename Iterator2>
size_t count_subsegments(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
    size_t answer = 0;
    for (; first1 != last1; ++first1) {
        bool ok = true;
        auto it1 = first1;
        auto it2 = first2;
        for (; it2 != last2; ) {
            if (it1 == last1) {
                ok = false;
                break;
            }
            if (*it1 != *it2) {
                ok = false;
                break;
            }
            ++it1;
            ++it2;
        }
        if (ok) {
            ++answer;
        }
    }
    return answer;
}