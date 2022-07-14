#include <iostream>
#include "RBT.cpp"

using namespace std;

template <typename Key, typename Value>
class my_map{
    private:
    RBT<Key, Value> rbt;

    public:

    typedef RBTIterator<Key, Value> iterator;

    iterator begin() {
        return rbt.begin();
    }

    iterator end() {
        return rbt.end();
    }

    void insert(pair<Key, Value> p) {
        rbt.insertion(p);
    }

    void erase(Key key) {
        rbt.deletion(key);
    }

    iterator find(Key key) {

        return rbt.find(key);
    }                   

    Value& operator[](Key key) {
        iterator it = rbt.find(key);
        if(it.get_cur() == nullptr) // insert new if not found
            rbt.insertion(make_pair(key, 0));
        return rbt.find(key).get_cur()->key_value.second;
    }
};