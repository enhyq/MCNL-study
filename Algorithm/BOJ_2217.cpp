/**
 * @author Eunhyeok Kwon
 * @date 2022-07-18 ~ 2022-07-19
 * @link https://www.acmicpc.net/problem/2217
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    // 1. get input N (num of ropes)
    // 2. each rope has strength
    // 3. when using multiple ropes together, weight is evenly distributed among used ropes
    // 4. find max weight that can be lifted using given ropes (doesn't have to use all ropes)

    // N개의 로프 1 ≤ N ≤ 100,000
    // 각 로프가 버틸 수 있는 최대중량 0 < K < 10,000
    int N, i, max_w = 0, weight = 0, temp;
    vector<int> ropes;

    cin >> N;

    for (i = 0; i < N; i++)
    { // get input
        cin >> temp;
        ropes.push_back(temp);
    }
    sort(ropes.begin(), ropes.end()); // sort in descending order

    for (int i = 0; i < N; i++)
    {
        weight = ropes[i] * (N - i);
        if (weight > max_w)
            max_w = weight;
    }
    cout << max_w << endl;

    return 0;
}
