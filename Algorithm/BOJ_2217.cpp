/**
 * @author Eunhyeok Kwon
 * @date 2022-07-18 ~ !
 * @link https://www.acmicpc.net/problem/2217
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    // 1. get input N (num of ropes)
    // 2. each rope has strength
    // 3. when using multiple ropes together, weight is evenly distributed among used ropes
    // 4. find max weight that can be lifted using given ropes (doesn't have to use all ropes)
    
    int N, i, max_w=0, sum=0, temp;
    cin >> N;
    for(i=0; i<N; i++) {
        cin >> temp;
        // if(temp > (sum+temp)
    }

    return 0;
}
