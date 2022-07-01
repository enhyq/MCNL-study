/**
 * @file trie.cpp
 * @author Eunhyeok Kwon
 * @brief 
 * @version 0.1
 * @date 2022-07-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

using namespace std;

/*
 * When you define struct, tag is a must
 * When using "typedef" you need a put type name at the end of definition
 */

typedef struct node_t{
    /*
     * In C++ you cannot initialize non-static default member
     */
    bool isUniqueWord;
    // inside struct, it doesn't know the type name "node" yet
    node_t *next;           // link to sibling
    node_t *child;          // link to child
} node;

class Trie {
    private:
    node *root;             // no syntax highlight?
    // struct node_t *root; // same thing as above

    public:

    void insertion(String &str) {

    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
