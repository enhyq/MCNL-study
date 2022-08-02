#include <iostream>
#include <vector>

// vector is from std library, so you either have to use std namespace or put "std::" in front
using namespace std;

/*
 * In C++, the only difference between struct and class is that
 * in class, members and base classes are private by default
 * in struct, they are public by default
 */

struct RMQ {
    int n;

    vector<int> rangeMin;
    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n*4);
        init(array, 0, n-1, 1);
    }

    int init(const vector<int>&array, int left, int right, int node) {
        if(left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
};


class segment_tree
{
private:
    
    


public:
    segment_tree(/* args */);
    ~segment_tree();
};

segment_tree::segment_tree(/* args */)
{
}

segment_tree::~segment_tree()
{
}
