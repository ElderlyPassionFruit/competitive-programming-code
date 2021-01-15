#include <string>
#include <vector>

std::string join(const std::vector<std::string>& tokens, char delimiter) {
    std::string answer = "";
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i != 0) {
            answer += delimiter;
        }
        answer += tokens[i];
    }
    return answer;
}
