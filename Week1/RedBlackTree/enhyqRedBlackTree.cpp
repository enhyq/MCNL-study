#include <iostream>

using namespace std;


typedef struct node {
    int value;
    bool isRed;         // picked red because all leaf node is black
    node* leftChild;
    node* rightChild;
};

/**
 * @brief For integer values
 * Duplicate values cannot be stored -> will implement in future
 */
class RedBlackTree {
    private:
    // array representation of RBT
    node* root;

    // actual size of the RBT
    int n = 0;  // do I need this?

    /**
     * @brief Function to reblance RBT
     * 
     */
    void Restructure() {

    }

    void Recolor() {

    }

    void Rebalance() {
        // 1. check for unblance

        // 2. 
    }

    public:
    // constructor. initialize node to NULL
    RedBlackTree() {
        root = NULL;
    }

    bool isEmpty() { return (root == NULL); }

    /**
     * @brief hmm.
     */
    void insertion(int value) {
        /**
         * left child => i*2
         * right child => i*2+1s
         */
        n++;                // increase actual size by 1

    }

    void deletion(int value) {

    }

    /**
     * @brief finds and return node with the agrument value
     * @return node* 
     */
    node* findNode(int value) {
        node* curNode = root;
        while(curNode != NULL) {
            if(value == curNode->value) return curNode;
            if(value < curNode->value) curNode = curNode->leftChild;
            else curNode = curNode->rightChild;
        }
        return NULL;
    }
};