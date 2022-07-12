/**
 * @author Eunhyeok Kwon
 * @date 2022-07-11 ~ 2022-07-11
 * @link https://www.acmicpc.net/problem/1712
 * 
 */
#include <iostream>

using namespace std;

// A + Bx <= Cx
// A + x(B-C) <= 0
// A/x + B-C <= 0
// A/x > -(B-C)
// 1/x > -(B-C)/A
// x > -A/(B-C)

int main(int argc, char const *argv[])
{
    // A = 고정 
    // B = 생상건당 비용
    // C = 판매 수익

    // 최초로 이익이 발생하는 판매량

    int A, B, C;
    cin >> A >> B >> C;
    if(B >= C) {
        cout << -1 << endl;
        return 0;
    }
    cout << -A/(B-C)+1 << endl;
    return 0;
}
