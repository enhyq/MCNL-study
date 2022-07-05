/**
 * @author Eunhyeok Kwon
 * @date 2022/06/30 ~ 2022/07/04
 * @link https://www.acmicpc.net/problem/2042
 */

#include <iostream>
#include <vector>

// 각 입력의 최대 Range가 long long TYPE 이기 때문에 더 많이 담을 수 있어야 한다.
#define TYPE long long int

using namespace std;


/*
 * 의문점: 각 input의 Range가 long long TYPE 인데
 * 출력 값은 왜 overflow가 허용 되는 건지?
 * 
 * 계산 해 보면 알겠지만 overflow가 발생하더라도 정답이 출력된다고 한다
 */


// RSQ = Range Sum Query
class RSQ {
    private:
    /**
     * since number range is from -2^64 ~ 2^64, which is range of long long TYPE
     */
    vector<TYPE> sumValue;
    TYPE arraySize;

    /**
     * actual initialization function 
     */
    TYPE init(vector<TYPE> &array, TYPE node, TYPE left, TYPE right) {
        if(left == right) return sumValue[node] = array[left];
        else {
            TYPE mid = (left + right) / 2;

            // 여기도 TYPE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            TYPE leftValue = init(array, node*2, left, mid);
            TYPE rightValue = init(array, node*2+1, mid + 1, right);
            return sumValue[node] = leftValue + rightValue;
        }
    }

    /**
     * finds the sum of the values in the range (left, right)
     */
    TYPE query(TYPE left, TYPE right, TYPE node, TYPE nodeLeft, TYPE nodeRight) {        
        if(left > nodeRight || right < nodeLeft) {
            // cout << nodeLeft << "~" << nodeRight << " " << 0 << endl;
            return 0; 
        }  // if nodeRange is out of Range
        if(left <= nodeLeft && nodeRight <= right) {
            // cout << nodeLeft << "~" << nodeRight << " " << sumValue[node] << endl;
            return sumValue[node];
        }  // if nodeRange is inside Range
        
        TYPE mid = (nodeLeft + nodeRight) / 2;
        TYPE leftValue = query(left, right, node*2, nodeLeft, mid);
        TYPE rightValue = query(left, right, node*2+1, mid+1, nodeRight);
        
        // cout << nodeLeft << "~" << nodeRight << " " << leftValue + rightValue << endl;
        return leftValue + rightValue;
    }

    /**
     * modify leaf node value and its ancestor segments
     */
    TYPE modify(TYPE index, TYPE newValue, TYPE node, TYPE left, TYPE right) {
        TYPE difference; // 여기 difference 또한 long long TYPE 타입이다 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 위dp type이라고 안쓰고 TYPE 라고 써서 여기서 너무 시간 낭비했다...
        if(left == right) {
            difference = newValue - sumValue[node];
            // cout << "difference: " << difference << "\n";
            sumValue[node] = newValue;
            return difference;
        }
        
        TYPE mid = (left + right) / 2;

        if(index <= mid)
            difference = modify(index, newValue, node*2, left, mid);
        else
            difference = modify(index, newValue, node*2+1, mid+1, right);
        
        sumValue[node] += difference;
        return difference;
    }

    // for debugging
    void print(TYPE node, TYPE left, TYPE right) {
        cout << sumValue[node] << " ";

        if(left == right) return;

        TYPE mid = (left + right) / 2;
        print(node*2, left, mid);
        print(node*2+1, mid + 1, right);
    }


    public:
    /**
     * @brief Construct a new RSQ object
     * 
     * @param array 
     */
    RSQ(vector<TYPE> &array) {
        arraySize = array.size();
        TYPE segmentTreeSize = arraySize * 4;
        sumValue.resize(segmentTreeSize);
        init(array, 1, 0, arraySize-1);
    }
 
    TYPE query(TYPE left, TYPE right) {
        return query(left, right, 1, 0, arraySize-1);
    }

    void modify(TYPE index, TYPE newValue) {
        if(index < 0 || arraySize-1 < index) return; // if modify index is out of range, don't do anything
        modify(index, newValue, 1, 0, arraySize - 1);
    }

    void printAll() {
        print(1, 0, arraySize-1);
        cout << endl;
    }

    // DELETE는 문제에서 요구하지 않으니...
};

int main(TYPE argc, char const *argv[])
{
    /* cin, cout fix */
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
     * N: number of numbers
     * K: number of modification
     * M: number of queries
     */
    // K, M을 알 필요가 있나?
    TYPE N, K, M;
    /*
     * 0 ≤ N ≤ 1,000,000
     * 1 ≤ M ≤ 10,000
     * 1 ≤ K ≤ 10,000
     */
    cin >> N >> K >> M;

    vector<TYPE> array;
    TYPE tempNum;
    TYPE i;
    for(i=0; i<N; i++) {
        cin >> tempNum;
        array.push_back(tempNum);
    }

    RSQ rsq(array);

    // 입력의 index는 1부터 시작한다!!
    TYPE o1, o2, o3; // o3은 newValue를 입력 받을 때도 사용되기 때문에
    for(i=0; i<K+M; i++) {
        // rsq.printAll();
        cin >> o1 >> o2 >> o3;
        if(o1 == 1) { // modify
            rsq.modify(o2-1, o3);
        }
        else {  // option == 2; query
            cout << rsq.query(o2-1, o3-1) << "\n";
        }
    }


    return 0;
}

// AC!