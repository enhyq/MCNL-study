/**
 * @author Eunhyeok Kwon
 * @date 2022-07-11 ~ 2022-07-12
 * @link https://www.acmicpc.net/problem/2846
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    // cur is at max 1000 in this problem
    int N, cur, prev=0, begin=1000, max=0;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> cur;
        // cout << "cur: " << cur << " ";
        // cout << "prev:" << prev << " ";
        // cout << "begin:" << begin << endl;
        if(i == 0) {
            begin = cur;                                // initial condition
        }
        else {
            if(cur <= prev){
                begin = cur;                            // reset begin if cur <= prev
            }
            if(cur-begin > max) {                       // check for new max
                max = cur-begin;
                // cout << "new max: " << max << endl;
            } 
        }
        prev = cur;                                     // set prev to cur
    }
    cout << max << endl;
    return 0;
}
