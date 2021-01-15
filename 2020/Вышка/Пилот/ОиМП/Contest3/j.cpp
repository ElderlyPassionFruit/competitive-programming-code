#include <algorithm>
#include <vector>

template <typename T>
void process(const std::vector<T>& data) {
    std::vector<T> filtered;

    std::copy_if(
        data.begin(),
        data.end(),
        std::inserter(filtered, filtered.begin()),
        [](const T& x) { return x > 0; });

    print_results(filtered.begin(), filtered.end());
}