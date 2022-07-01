#include <iostream>
#include <vector>

using namespace std;

/*
 * this is example code is from the book "알고리즘2" 
 */


// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
// RMQ -> Range Minimum Query
struct RMQ
{
    /* data */
    int n;                                              // size of array (number of nodes in segment tree)
    vector<int> rangeMin;                               // segment tree that stores minimum value of each segment
    const int INT_MAX = numeric_limits<int>::max();     // very large number (infinity) so that it does not effect finding minimum value

    /* 
     * constructor of RMQ,
     * receives array of numbers as parameter and creates segment tree from it
     */
    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n-1, 1); // begin node from 1 for simpler calculation
    }

    /*
     * recursive function to initialize segment tree for RMQ
     */
    int init(const vector<int>& array, int left, int right, int node) {
        if(left == right)
            return rangeMin[node] = array[left];

        int mid = (left + right) / 2;
        /*                  array, left,  right,   node          */
        int leftMin  = init(array, left,  mid,     node * 2);             // defining left segment
        int rightMin = init(array, right, min + 1, node * 2 + 1);   // defining right segment
        return rangeMin[node] = min(leftMin, rightMin);             // set current node as minimum of left and right segment
        // return current value for its parent to process min(left, right);
    }

    /*
     * query function
     * gets left and right range as parameter and finds the minimum number in the rangeMin vector
     * return minimum number
     * this function will be used internally
     */
    int query(int left, int right,
              int node, int nodeLeft, int nodeRight) {
        // if range does not overlap at all
        if(right < nodeLeft || nodeRight > left)
            return INT_MAX;
        // if range completely overlap
        if(left <= nodeLeft && nodeRight < left)
            return rangeMin[node];
        
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node*2, nodeLeft, mid),
                   query(left, right, node*2+1, mid+1, nodeRight));
    }

    /*
     * interface to call query from outside
     */
    int query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }


    /*
     * Modifying segment tree (simple)
     * updating replace newValue at index of the segment tree
     * then recalculates the segment tree values to fit to the modified changes
     */
    int update(int index, int newValue,
               int node, int nodeLeft, int nodeRight) {
        
        if(index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        // when index is found, replace the node value to newValue
        // or you could put (index == nodeLeft && index == nodeRight)
        if(nodeLeft == nodeRight)
            return rangeMin[node] = newValue;

        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(
            update(index, newValue, node*2, nodeLeft, mid);
            update(index, newValue, node*2+1, mid+1, nodeRight);
        )
    }

    /*
     * interface to call update function from outside
     */
    int update(int index, int newValue) {
        update(index, newValue, 1, 0, n-1);
    }

};
