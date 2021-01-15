#include <iostream>
#include <vector>

std::vector<long long> a;
long long a_size = 0;

void siftUp(long long i)
{
    while (a[i] < a[(i - 1) / 2])
    {
        std::swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void siftDown(long long i)
{
    while (2 * i + 1 < a_size)
    {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if (a[left] > a[i])
            if (right < a_size and a[right] < a[left])
                j = right;
        if (a[i] < a[j])
            break;
        std::swap(a[i], a[j]);
        i = j;
    }
}

void insert(long long key)
{
    a_size++;
    a.push_back(key);
    siftUp(a_size-1);
}

long long extractMin()
{
    long long min = a[0];
    a[0] = a[a_size - 1];
    a_size--;
    a.pop_back();
    siftDown(0);
    return min;
}

int main()
{
    long long m;
    std::cin >> m;
    for (long long i = 0; i < m; ++i)
    {
        long long ch;
        std::cin >> ch;
        if (ch < 0)
            std::cout << extractMin() << std::endl;
        else
            insert(ch);
    }
    return 0;
}