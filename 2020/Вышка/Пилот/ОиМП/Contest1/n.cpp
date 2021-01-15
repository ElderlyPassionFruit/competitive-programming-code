#include <string_view>

bool checkPalindrome(const std::string_view& forCheck) {
    if (forCheck.empty()) return true;
    for (size_t i = 0; i < forCheck.size() - 1 - i; ++i) {
        if (forCheck[i] != forCheck[forCheck.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

int countPalindromes(const std::string_view& forCount) {
    int counter = 0;
    for (size_t i = 0; i < forCount.size(); ++i) {
        if (forCount[i] == ' ') continue;
        size_t j = i;
        while (j < forCount.size() && forCount[j] != ' ') ++j;
        counter += checkPalindrome(forCount.substr(i, j - i));
        i = j;
    }
    return counter;
}
