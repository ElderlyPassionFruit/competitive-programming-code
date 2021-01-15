#include <cctype>
#include <utility>
#include <string>

bool isVowel(char character) {
    character = tolower(character);
    if (character == 'a') return true;
    if (character == 'e') return true;
    if (character == 'i') return true;
    if (character == 'o') return true;
    if (character == 'u') return true;
    if (character == 'y') return true;
    return false;
}

std::pair<size_t, int> FindVowels(const std::string &s, const size_t &pos) {
    std::pair<size_t, int> answer;
    answer.first = std::string::npos;
    for (size_t i = pos; i < s.size(); ++i) {
        if (!isVowel(s[i])) {
            continue;
        }
        answer.first = i;
        answer.second = 1;
        while (answer.first + answer.second < s.size()) {
            if (!isVowel(s[answer.first + answer.second])) {
                break;
            }
            ++answer.second;
        }
        break;
    }
    return answer;
}
