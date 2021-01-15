template< class It, class T >
void fill_range(It first, It last, const T& value) {
    for (; first != last; ++first) {
        *first = value;
    }
}