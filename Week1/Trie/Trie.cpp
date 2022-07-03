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
#include <string>

using namespace std;

namespace enhyq {
    class Trie;
}

/*
 * When you define struct, tag is a must
 * When using "typedef" you need a put type name at the end of definition
 */

typedef struct node_t{
    /*
     * In C++ you cannot initialize non-static default member
     */
    char value;             // only 256 variations for now
    bool isUniqueWord;
    // inside struct, it doesn't know the type name "node" yet
    node_t *next;           // link to sibling
    node_t *child;          // link to child

    /* basic constructor for node */
    node_t() {
        value = '\0';
        isUniqueWord = false;
        next = NULL;
        child = NULL;
    }
} node;

class enhyq::Trie {
    private:
    node *root;             // no syntax highlight?
    // struct node_t *root; // same thing as above

    public:

    /* Constructor 
     * initializes root
     */
    Trie() {
        root = new node();
    }

    /*
     * search for character among siblings
     */
    node* searchInSibling(node *n, char c) {
        while(n != NULL) {
            if(n->value == c)
                return n;
            else
                n = n->next;
        }
        return NULL;
    }

    /*
     * search for character among siblings
     */
    node* getLastSibling(node *n) {
        if(n == NULL) return NULL;

        while(n->next != NULL) {
            n = n->next;
        }
        return n;
    }

    /*
     * insert nodes...
     */
    void insertion(const string &str) {
        // 1. 내려갈 수 있는 만큼 내려가기
        int i = 0;
        node *current_node = root;
        while(str[i] != '\0') {
            if (searchInSibling(current_node, str[i]) == NULL) break;
            current_node = searchInSibling(current_node, str[i]);
            current_node = current_node->child;
            i++;
        }
        // 2.0 처음에는 last sibling으로 추가해야 한다
        bool first = true;
        // 2. child node 추가하기
        while(str[i] != '\0') {
            node *newNode = new node;
            newNode->value = str[i];
            newNode->isUniqueWord = false;
            newNode->next = NULL;
            newNode->child = NULL;
            if(first) {
                current_node = getLastSibling(current_node);
                current_node->next = newNode;
                current_node = newNode;
                first = false;
            }
            else {
                current_node->child = newNode;
                current_node = newNode;
            }
            i++;
        }
        // 3. 마지막 node에 isUniqueWord 마킹하기
        // 이미 trie에 들어 있는 단어면 바로 여기로 내려와서 isUniqueWord 만 체크된다.
        current_node->isUniqueWord = true;
    }

    /*
     * Search for input string in trie
     * return true if found
     */
    bool search(const string &str) {
        int i = 0;          // index for iterating over string
        node *current_node = root;
        while(str[i] != '\0') { // all string ends with '\0'
            if (searchInSibling(current_node, str[i]) == NULL) return false;    // 자기 자신과 sibling중 일치하는 character를 찾는다
            current_node = searchInSibling(current_node, str[i]);
            // cout << current_node->value << " " << current_node->isUniqueWord << endl;
            if(str[i+1] != '\0')
                current_node = current_node->child;
            i++;
        }
        if(current_node->isUniqueWord) return true;
        return false;
    }


    // singly linked list로 구현해서 deletion이 좀 어려울 것 같다..
    void deletion(const string &str) {
        // since I used singly linked list, it might be better to use recursive function
        // 1. reach the bottom and remove

        // 2. 
    }

    /*
     * prints out all the words stored in trie
     */
    void print() {
        
    }

};

int main(int argc, char const *argv[])
{
    /* code */
    enhyq::Trie t; // = new enhyq::Trie();
    t.insertion("hello");
    t.insertion("hellbo");
    t.insertion("bye");
    t.insertion("eunhyeok");

    // true
    cout << t.search("hello") << endl;
    cout << t.search("hellbo") << endl;
    cout << t.search("bye") << endl;
    cout << t.search("eunhyeok") << endl;

    // false
    cout << t.search("hell") << endl;
    cout << t.search("hellbe") << endl;
    cout << t.search("byee") << endl;
    cout << t.search("") << endl;

    return 0;
}
