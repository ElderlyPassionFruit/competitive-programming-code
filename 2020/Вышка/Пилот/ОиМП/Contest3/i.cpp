template <typename It, typename OutputIt>
OutputIt sideways_merge(It first1, It last1, It first2, It last2, OutputIt out) {
    while (first1 != last1 && first2 != last2) {
        It now2 = last2;
        --now2;
        if (*first1 < *now2) {
            *out = *first1;
            ++first1;
        } else {
            *out = *now2;
            --last2;
        }
        ++out;
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
    while (first2 != last2) {
        --last2;
        *out = *last2;
        ++out;
    }
    return out;
}