/**
 * @author Eunhyeok Kwon
 * @date 2022/06/30 ~ 
 * @link https://www.acmicpc.net/problem/2042
 */

#include <iostream>
#include <vector>

// 각 입력의 최대 Range가 long long int 이기 때문에 더 많이 담을 수 있어야 한다.
#define TYPE long long int

using namespace std;


/*
 * 의문점: 각 input의 Range가 long long int 인데
 * 출력 값은 왜 overflow가 허용 되는 건지?
 */


// RSQ = Range Sum Query
class RSQ {
    private:
    /**
     * since number range is from -2^64 ~ 2^64, which is range of long long int
     */
    vector<int> sumValue;
    int arraySize;

    /**
     * actual initialization function 
     */
    int init(vector<int> &array, int node, int left, int right) {
        if(left == right) return sumValue[node] = array[left];
        else {
            int mid = (left + right) / 2;
            int leftValue = init(array, node*2, left, mid);
            int rightValue = init(array, node*2+1, mid + 1, right);
            return sumValue[node] = leftValue + rightValue;
        }
    }

    /**
     * finds the sum of the values in the range (left, right)
     */
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {        
        if(left > nodeRight || right < nodeLeft) {
            // cout << nodeLeft << "~" << nodeRight << " " << 0 << endl;
            return 0; 
        }  // if nodeRange is out of Range
        if(left <= nodeLeft && nodeRight <= right) {
            // cout << nodeLeft << "~" << nodeRight << " " << sumValue[node] << endl;
            return sumValue[node];
        }  // if nodeRange is inside Range
        
        int mid = (nodeLeft + nodeRight) / 2;
        int leftValue = query(left, right, node*2, nodeLeft, mid);
        int rightValue = query(left, right, node*2+1, mid+1, nodeRight);
        
        // cout << nodeLeft << "~" << nodeRight << " " << leftValue + rightValue << endl;
        return leftValue + rightValue;
    }

    /**
     * modify leaf node value and its ancestor segments
     */
    int modify(int index, int newValue, int node, int left, int right) {
        int difference;
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

    // for debugging
    void print(int node, int left, int right) {
        cout << sumValue[node] << " ";

        if(left == right) return;

        int mid = (left + right) / 2;
        print(node*2, left, mid);
        print(node*2+1, mid + 1, right);
    }


    public:
    /**
     * @brief Construct a new RSQ object
     * 
     * @param array 
     */
    RSQ(vector<int> &array) {
        arraySize = array.size();
        int segmentTreeSize = arraySize * 4;
        sumValue.resize(segmentTreeSize);
        init(array, 1, 0, arraySize-1);
    }
 
    int query(int left, int right) {
        return query(left, right, 1, 0, arraySize-1);
    }

    void modify(int index, int newValue) {
        if(index < 0 || arraySize-1 < index) return; // if modify index is out of range
        modify(index, newValue, 1, 0, arraySize - 1);
    }

    void printAll() {
        print(1, 0, arraySize-1);
        cout << endl;
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

    vector<int> array;
    int tempNum;
    int i;
    for(i=0; i<N; i++) {
        cin >> tempNum;
        array.push_back(tempNum);
    }

    RSQ rsq(array);

    int o1, o2, o3; // 입력의 index는 1부터 시작한다!!
    for(i=0; i<K+M; i++) {
        // rsq.printAll();
        cin >> o1 >> o2 >> o3;
        if(o1 == 1) { // modify
            rsq.modify(o2-1, o3);
        }
        else {  // option == 2; query
            cout << rsq.query(o2-1, o3-1) << endl;
        }
    }


    return 0;
}


// 도대체 어디서 틀렸는지 모르겠다