#include <iostream>
#include "RBT.cpp"

using namespace std;

template <typename Key, typename Value>
class my_map{
    private:
    RBT<Key, Value> rbt;

    public:
    void insert(pair<Key, Value> p) {
        rbt.insertion(p);
    }

    void erase(Key key) {
        // TODO
    }

    // RBT<Key, Value>* find()  
    pair<Key, Value>* find(Key key) {
        return rbt.find(key);
    }                   

    Value &operator[](Key key) {
        return rbt.find(key)->second;
    }
};