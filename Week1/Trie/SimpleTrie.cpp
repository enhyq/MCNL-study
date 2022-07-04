/*
 * code from "알고리즘 문제 해결 전략"
 */

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// 알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

struct TrieNode {
    TrieNode* children[ALPHABETS];
    bool terminal;

    /*
     * constructor
     * the ':' operator(?) is used for initializing member variable before executing the body of the constructor
     */
    TrieNode() : terminal(false) {
        /*
         * memset
         * Fill block of memory
         * "Sets the first num bytes of the block of memory pointed by ptr to the specified value"
         * void * memset ( void * ptr, int value, size_t num );
         *  ptr: "Pointer to the block of memory to fill."
         *  value: "Value to be set."
         *  num: "Number of bytes to be set to the value."
         */ 
        memset(children, 0, sizeof(children));
        // loop를 돌려서 각 index를 기본 값으로 초기화 하기 보다 memset으로 0으로 초기화 한다
        // C++ 에서 NULL은 interal constant zero이기 떄문에 NULL로 초기화 한 것이라고 보면 된다
    }

    /*
     * destructor
     */
    ~TrieNode() {
        for(int i=0; i<ALPHABETS; ++i) {
            if(children[i])
                delete children[i];
        }
    }

    /*
     * insertion
     */
    void insert(const char* key) {
        if(*key == 0) // same as (*key == '\0'), EOF
            terminal = true;
        else {
            int next = toNumber(*key);          // next child
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1);    // next letter
        }
    }

    /*
     * find
     * returns the pointer to the end node of the found key
     * return NULL if not found
     */
    TrieNode* find(const char* key) {
        if(*key == 0) return this;

        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key+1);
    }

    // DELETE FUNCTION?

}; // struct ends with semi-colon (;)