/**
 * @author Eunhyeok Kwon
 * @date 2022/07/04 ~ 2022/07/04
 * @link https://www.acmicpc.net/problem/10868
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// RMQ = Range Minimum Query
class RMQ {
    private:
    vector<int> minValue;
    int arraySize;

    /**
     * actual initialization function 
     */
    int init(vector<int> &array, int node, int left, int right) {
        if(left == right) return minValue[node] = array[left];
        else {
            int mid = (left + right) / 2;
            int leftValue = init(array, node*2, left, mid);
            int rightValue = init(array, node*2+1, mid + 1, right);
            return minValue[node] = min(leftValue, rightValue);
        }
    }

    /**
     * finds the sum of the values in the range (left, right)
     */
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {        
        if(left > nodeRight || right < nodeLeft) {
            return INT_MAX; 
        }  // if nodeRange is out of Range
        if(left <= nodeLeft && nodeRight <= right) {
            return minValue[node];
        }  // if nodeRange is inside Range
        
        int mid = (nodeLeft + nodeRight) / 2;
        int leftValue = query(left, right, node*2, nodeLeft, mid);
        int rightValue = query(left, right, node*2+1, mid+1, nodeRight);
        
        return min(leftValue, rightValue);
    }


    public:
    /**
     * Construct a new RMQ object
     */
    RMQ(vector<int> &array) {
        arraySize = array.size();
        int segmentTreeSize = arraySize * 4;
        minValue.resize(segmentTreeSize);
        init(array, 1, 0, arraySize-1);
    }
 
    int query(int left, int right) {
        return query(left, right, 1, 0, arraySize-1);
    }
};

int main(int argc, char const *argv[])
{
    /* 
     * C++ 에서 for문에서 입출력을 할 때에는 
     * 아래와 같이 설정을 해줘야 시간 초과 틀렸습니다를 면할 수 있다.
     */
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    /*
     * N: number of numbers
     * M: number of queries
     */
    int N, M;
    cin >> N >> M;

    vector<int> array;
    int tempNum;
    int i;
    for(i=0; i<N; i++) {
        cin >> tempNum;
        array.push_back(tempNum);
    }

    RMQ rmq(array);

    int o1, o2; // 입력의 index는 1부터 시작한다!!
    for(i=0; i<M; i++) {
        cin >> o1 >> o2;
        cout << rmq.query(o1-1, o2-1) << "\n";
    }


    return 0;
}