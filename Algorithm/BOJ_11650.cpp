/**
 * @author Eunhyeok Kwon
 * @date 2022-08-02 ~ 2022-08-02
 * @link https://www.acmicpc.net/problem/11650
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 시간 제한: 1초 
 *
 * 점의 개수 N (1 ≤ N ≤ 100,000)
 * i번점의 위치 xi와 yi (-100,000 ≤ xi, yi ≤ 100,000)
 * 좌표는 항상 정수
 * 위치가 같은 두 점은 없다
 * 
 * 좌표를 x좌표가 증가하는 순으로, x좌표가 같으면 y좌표가 증가하는 순서로 정렬
 */

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, x, y;
    cin >> N;

    vector<pair<int, int> > v;

    for(int i=0; i<N; i++)
    {
        cin >> x >> y;
        v.push_back(make_pair(x, y));
    }

    sort(v.begin(), v.end());

    for(int i=0; i<N; i++)
    {
        cout << v.at(i).first << " " << v.at(i).second << "\n";
    }

    return 0;
}
