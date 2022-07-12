/**
 * @author Eunhyeok Kwon
 * @date 2022-07-12 !
 * @link https://www.acmicpc.net/problem/17212
 */

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    // 1 2 5 7
    int N, i, j, count=0, temp;
    cin >> N;
    int coin_type[] = {7,5,2,1};                                // 4 types
    for(i=0; i<3; i++) {
        if(N < coin_type[i]) continue;                          // if N is less then coin type, skip
        temp = N / coin_type[i];                                // calculate how much of this coin type can be used
        // cout << N << "/" << coin_type[i] << " " << temp << endl;
        N -= temp * coin_type[i];
        count += temp;
    }
    count += N;
    cout << count << endl;
    return 0;
}
