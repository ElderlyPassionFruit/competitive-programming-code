#include <vector>
#include <cstdio>
#include <algorithm>

static constexpr int MAX = 70000000;

std::vector<int> items;
std::vector<int> sufSum;
int stepsCounter;   

void RunKnapsack(int n, int X, int sum, int i) {
    ++stepsCounter;
    if (stepsCounter >= MAX) {
        printf("NO\n");
        exit(0);
    }
    if (sum == X) {
        printf("%d\n", stepsCounter);
        printf("YES\n");
        exit(0);
    }
    if ((i == n) || (sum > X) || (sum + sufSum[i] < X))
        return;
    RunKnapsack(n, X, sum, i + 1);
    RunKnapsack(n, X, sum + items[i], i + 1);
}

int main() {
    int n, X;
    scanf("%d%d", &n, &X);
    items.resize(n);
    sufSum.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &items[i]);
    }
    sort(items.begin(), items.end());
    reverse(items.begin(), items.end());
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1)
            sufSum[i] = items[i];
        else
            sufSum[i] = sufSum[i + 1] + items[i];
    }
    RunKnapsack(n, X, 0, 0);
    printf("NO\n");
}