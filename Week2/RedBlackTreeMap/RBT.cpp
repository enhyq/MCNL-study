#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * Class template
 * insert()
 * erase()
 * find()
 * begin()
 * end()
 * [] (operator overloading)
 * iterator (first = key, second = value)
 */


enum { BLACK, RED };
enum { LEFT, RIGHT};

/**
 * @brief node structure used as an element in Red Black Tree
 * 
 * @tparam Key 
 * @tparam Value 
 */
template <typename Key, typename Value>
struct node {
    
    bool color;
    Key key;
    Value value;
    node *parent;
    node *child[2];

    /**
     * @brief Construct a new node object with value
     */
    node(Key key, Value value) {
        color = RED;
        this->key = key;
        this->value = value;
        parent = child[0] = child[1] = NULL;    // parent is also initially NULL
    }
};

/**
 * @brief Red Black Tree which is made with node that has {key, value}
 * 
 * @tparam Key 
 * @tparam Value 
 */
template <typename Key, typename Value>
class RBT {
    private:
    node<Key, Value> *root;

    // prints element in inorder traversal (recursive)
    void print_inorder(node<Key, Value>* N) {
        if(N == NULL) return;
        
        print_inorder(N->child[LEFT]);
        cout << "[" << N->key << "]";
        print_inorder(N->child[RIGHT]);
    }

    void print_level_order(node<Key, Value>* N) {
        cout << "[" << N->value << "]";
        queue<node<Key, Value>*> q;
        
    }

    public:
    // Constructs a new RBT object with NULL root
    RBT() {
        root = NULL;
    }

    /**
     * @brief comparing the keys, it finds the node that is to be the parent of the inserted new node
     * 
     * @param key 
     * @return node* 
     */
    node<Key, Value>* find_parent_node(Key key) {
        node<Key, Value> *N = root;
        if(N == NULL) return NULL;                          // empty, no parent
        while(true) {
            if(key < N->key) {                          // if value is smaller than current node -> goto left child
                if(N->child[LEFT] == NULL) return N;
                else N = N->child[LEFT];
            }
            else if(key > N->key) {                     // if value is greater than current node -> goto right child
                if(N->child[RIGHT] == NULL) return N;           
                else N = N->child[RIGHT];
            }
            // didn't implement case when (value == N->value)
        }
    }

    void insertion(Key key, Value value) {
        node<Key, Value> *N = new node<Key, Value>(key, value);

        if(root == NULL) {                                  // if empty
            N->color = BLACK;
            root = N;
            return;
        }

        node<Key, Value> *P = find_parent_node(key);
        N->parent = P;
        int dir = (N->key < P->key)?LEFT:RIGHT;         // if the new node is smaller than Parent, dir is LEFT, else RIGHT
        P->child[dir] = N;                                  // add node as child of parent
        
        while(true) {
            if(P->color == BLACK) return;                       // if parent is black, is balanced
            // parent is RED
            node<Key, Value> *G = P->parent;                                // grand parent. If parent is RED, there must be non NULL G
            node<Key, Value> *U = (P->key < G->key)?G->child[RIGHT]:G->child[LEFT];
            // If U is BLACK or NIL
            if(U == NULL || U->color == BLACK) {
                if(G->child[dir] != P) {                        // if inner node
                    G->child[1-dir] = N;
                    N->child[1-dir] = P;
                    P->child[dir] = NULL;
                    dir = 1-dir;
                    P = N;
                    N = P->child[dir];
                }
                G->child[dir] = P->child[1-dir];
                if(G->child[dir] != NULL)
                    G->child[dir]->parent = G;

                if(G == root)
                    root = P;
                else
                    G->parent->child[dir] = P;
                P->parent = G->parent;

                P->child[1-dir] = G;
                G->parent = P;

                P->color = BLACK;
                G->color = RED;
                return;                                         // BREAK after restructuing, it's balanced
            }
            // If U is RED                                      // do recoloring
            else {
                P->color = U->color = BLACK;
                G->color = RED;
                N = G;                                          // repeat the process
                if(N->parent == NULL) {
                    // N == root
                    if(N->color == RED) N->color = BLACK;
                    break;
                }
                // N parent is NULL when N is root
                P = N->parent;
            }
        }
    }

    void deletion(int value) {
        // 0. find the node to be deleted
        // set u and v. {v: node to delete, u: node that replaces v}
        node<Key, Value> *v;
        node<Key, Value> *u;
        // 1. Do standard BST deletion
            // a. if node to be deleted
        

        // 2. if either u or v is RED, mark the replaced child as BLACK and DONE.

        // 3. if both u and v is BLACK
        // 3.2 Let sibling of v be s

            // a. if s is BLACK and at least a child of s is RED, let the red child be r -> rotation
                // i. LL case)      s and r are left child of its parent
                // ii. LR case)     s is left child, r is right child
                // iii. RR case)    s are r are right child of its parent
                // iv. RL case)     s is right child, l is left child
            
            // b. if s is BLACK and both of its children are BLACK -> recolor, and recur for the parent if its BLACK
            // if parent is RED, make it BLACK and DONE.

            // c. if s is RED
            // perform rotation to move old sibling up, recolor the sibling and parent
            // find new sibling, it will be black
                // i. Left case)    s is left child of its parent       ->      right rotate parent p
                // ii. Right case)  s is right child of its parent      ->      left rotate parent p

        // 3.3 if u is root, make it single BLACK and return

        // ** situation where both u and v are RED cannot occur
    }

    void print() {
        cout << "inorder print: ";
        print_inorder(root);
        cout << endl;
    }

};

int main(int argc, char const *argv[])
{
    /* code */

    RBT<string, int> rbt;
    rbt.insertion("ab", 10);
    rbt.insertion("b", 99);
    rbt.insertion("zz", 1);
    rbt.insertion("c", 0);
    rbt.print();

    return 0;
}
