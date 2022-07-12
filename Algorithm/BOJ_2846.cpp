/**
 * @author Eunhyeok Kwon
 * @date 2022-07-11 ~
 * @link https://www.acmicpc.net/problem/2846
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    // cur is at max 1000 in this problem
    int N, cur, prev=0, begin, max=0;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> cur;
        cout << "cur: " << cur << " ";
        cout << "prev:" << prev << " ";
        cout << "begin:" << begin << endl;
        if(i==0) {
            begin = cur;
        }
        else if(cur <= prev){
            begin = cur;               // reset prev
        }
        if(cur-begin > max) {
            max = cur-begin;
            cout << "new max: " << max << endl;
        }
        prev = cur;
    }
    cout << max;
    return 0;
}
