#include <iostream>
#include <string>

template<typename T1> void Print(const T1& forOutput, const std::string& delimiter) {
    bool first = true;
    for (const auto& i : forOutput) {
        if (!first) {
            std::cout << delimiter;
        } else {
            first = false;
        }
        std::cout << i;
    }
    std::cout << "\n";
}
