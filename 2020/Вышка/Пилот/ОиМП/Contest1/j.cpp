#include <utility>
#include <vector>

std::pair<size_t, size_t> max_element(const std::vector<std::vector<int>>& matrix) {
    std::pair<size_t, size_t> answer;
    answer.first = 0;
    answer.second = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[answer.first][answer.second] < matrix[i][j]) {
                answer.first = i;
                answer.second = j;
            }
        }
    }
    return answer;
}
