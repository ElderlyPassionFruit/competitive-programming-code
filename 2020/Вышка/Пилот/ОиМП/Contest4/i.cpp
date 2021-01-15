#include <utility>
#include <vector>

template<typename T>
class Table{
private:
    size_t n, m;
    std::vector<std::vector<T>> data;

public:
    Table(size_t _n, size_t _m)
        : n(_n)
        , m(_m) {
        data.assign(n, std::vector<T>(m, T()));
    }
    std::vector<T>& operator[](size_t i) {
        return data[i];
    }
    std::vector<T> operator[](size_t i) const {
        return data[i];
    }
    void resize(size_t _n, size_t _m) {
        n = _n, m = _m;
        data.resize(n, std::vector<T>(m, T()));
        for (size_t i = 0; i < n; ++i) {
            data[i].resize(m, T());
        }
    }
    std::pair<size_t, size_t> size() const {
        return std::make_pair(n, m);
    }
};