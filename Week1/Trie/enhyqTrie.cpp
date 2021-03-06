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
    // 
    void deletion(const string &str) {
        // since I used singly linked list, it might be better to use recursive function

        // do search first, to ensure that the word to delete exist in this trie

        // travel down recursive
        // longest word is about 25 letters? so recursive should be fine(..???)

        // 1. reach the end letter of the word
        //   a. if the end of the word doesn't have child -> return NULL
        //      i. if sibling exist -> delete node and return sibling
        //      ii. if no sibling -> delete node and return NULL
        //   b. if the end of the word has child -> just set isUniqueWord to false, return node

    }

    // input str should exist in the DS

    /* 
     * 
     */
    node* deletion_(node* current_node, int index, const string &str) {
        // if current letter is the last one
        if(str[index+1] == '\0') {
            if(current_node->child != NULL) {   // has child
                current_node->isUniqueWord = false;
                return current_node;
            }
            else {
                if(current_node->next) {        // no child, has next sibling
                    
                }
                else {                          // no child, no next sibling

                }
            }
        }
        else { // not end of the word... make recursive call
            // need to find the node with string

            // 1. if next letter is direct child
            if(current_node->value == str[index]) {
                current_node->child = deletion_(current_node->child, index++, str);
                return current_node;
            }
            // 2. if letter is one of the next sibling
            else {
                node *firstChild = current_node;
                current_node->next = searchInSibling(current_node->child, str[index+1]);   
                current_node->next = deletion_(current_node->child, index++, str);
            }
            
        }
        // 
    }


    /*
     * prints out all the words stored in trie
     */
    void print() {
        // travel all branches in trie and print whenever isUniqueWord is true
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


/*
 *
 * 생각해 보니 이렇게 구현 하면 Trie를 사용하는 이점이 사라진다.
 * 검색을 빠르게 하기 위해 만들었는데 children을 index로 바로 접근하지 못하고
 * sibling들을 차례로 넘어가면서 비교해야 하기 때문에 일반적인 array를 사용하는 것 같이
 * worst case에서는 결국 모든 문자열과 일일이 비교해 봐야 하기 때문이다.
 * 
 * 그래서 차라리 hashed map과 같이 indexing이 빠른 구조를 사용해야 한다.
 * 결론적으로 Simple Trie는 메모리를 많이 사용할 수 밖에 없는 구조이다.. (?)
 *
 */