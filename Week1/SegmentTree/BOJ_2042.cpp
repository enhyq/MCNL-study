/**
 * @author Eunhyeok Kwon
 * @date 2022/06/30 ~ 
 * @link https://www.acmicpc.net/problem/2042
 */

#include <iostream>
#include <vector>

#define TYPE long long int

using namespace std;

// RSQ = Range Sum Query
class RSQ {
    private:
    /**
     * since number range is from -2^64 ~ 2^64, which is range of long long int
     */
    vector<TYPE> sumValue;
    int arraySize;

    /**
     * actual initialization function 
     */
    int init(vector<TYPE> &array, int node, int left, int right) {
        if(left == right) return sumValue[node] = array[left];
        else {
            int mid = (left + right) / 2;
            int left = init(array, node*2, left, mid);
            int right = init(array, node*2+1, mid + 1, right);
            return sumValue[node] = left + right;
        }
    }

    /**
     * finds the sum of the values in the range (left, right)
     */
    TYPE query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if(left > nodeRight || right < nodeLeft) return 0;
        if(left <= nodeLeft && nodeRight <= right) return sumValue[node];

        int mid = (left + right) / 2;
        int leftSegment = query(left, right, node*2, nodeLeft, mid);
        int rightSegment = query(left, right, node*2+1, mid+1, nodeRight);
        return leftSegment + rightSegment;
    }

    /**
     * modify leaf node value and its ancestor segments
     */
    TYPE modify(int index, TYPE newValue, int node, int left, int right) {
        TYPE difference;
        if(left == right) {
            difference = newValue - sumValue[node];
            sumValue[node] = newValue;
            return difference;
        }
        
        int mid = (left + right) / 2;
        if(index <= mid)
            difference = modify(index, newValue, node*2, left, mid);
        else
            difference = modify(index, newValue, node*2+1, mid + 1, right);
        
        sumValue[node] += difference;
        return difference;
    }



    public:
    /**
     * @brief Construct a new RSQ object
     * 
     * @param array 
     */
    RSQ(vector<TYPE> &array) {
        arraySize = array.size();
        int segmentTreeSize = arraySize * 4;
        sumValue.resize(segmentTreeSize);
        init(array, 1, 0, arraySize-1);
    }
 
    TYPE query(int left, int right) {
        return query(left, right, 1, 0, arraySize-1);
    }

    void modify(int index, TYPE newValue) {
        modify(index, newValue, 1, 0, arraySize - 1);
    }

    // DELETE는 문제에서 요구하지 않으니...
};

int main(int argc, char const *argv[])
{
    /* code */
    /*
     * N: number of numbers
     * K: number of modification
     * M: number of queries
     */
    // K, M을 알 필요가 있나?
    int N, K, M;
    cin >> N >> K >> M;

    vector<TYPE> array;
    TYPE tempNum;
    int i;
    for(i=0; i<N; i++) {
        cin >> tempNum;
        array.push_back(tempNum);
    }

    RSQ rsq(array);

    int o1, o2, o3;
    for(i=0; i<K+M; i++) {
        cin >> o1 >> o2 >> o3;
        if(o1 == 1) { // modify
            rsq.modify(o2, o3);
        }
        else {  // option == 2; query
            cout << rsq.query(o2, o3) << endl;
        }
    }


    return 0;
}
