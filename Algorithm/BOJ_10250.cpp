/**
 * @author Eunhyeok Kwon
 * @date 2022-07-25 ~ 2022-07-26
 * @link https://www.acmicpc.net/problem/10250
 */

/*
 * << ACM Hotel >>
 * Problem Description
 *  W x H shaped 2D hotel
 *  door and elevator at left side
 *  distance from door to elevator and distance traveled by elevator doesn't matter
 *  closest room and lower floor is always preferred 
 *  room begins 1 from left 
 *  When W, H and N, the Nth guest to the hotel is given
 *  print out the most preferred room to assign to the guest
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    int T, W, H, N, floor, room;
    cin >> T;
    while(T--)
    {
        cin >> H >> W >> N;

        floor = N % H;
        floor = floor?:H;

        room = (N-1)/H + 1;

        cout << floor << setfill('0') << setw(2) << room << endl;
    }
    return 0;
}