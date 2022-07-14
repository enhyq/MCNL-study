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
    pair<Key, Value> key_value;
    node *parent;
    node *child[2];

    /**
     * @brief Construct a new node object with value
     */
    node(pair<Key, Value> key_value) {
        color = RED;
        this->key_value = key_value;
        parent = child[0] = child[1] = NULL;    // parent is also initially NULL
    }
};


template <typename Key, typename Value>
class RBTIterator{
    private:
    node<Key, Value> *cur;

    /**
     * @brief Using inorder traversal, it finds and returns the next node
     * 
     * @param N node to begin searching
     * @return node<Key, Value>* 
     */
    node<Key, Value>* next_node(node<Key, Value>* N) {
        // if no right child
            // while(current node is not root)
                // go up and check if I am right child
                // if left child
                    // return current node
                // else
                    // if root
                        // return nullptr
        // else
            // find min in the rigth sub tree
        int dir;
        node<Key, Value>* P;
        if(N->child[RIGHT] == NULL) {
            while(N->parent != NULL) {
                P = N->parent;
                dir = (P->child[LEFT] == N)? LEFT : RIGHT;
                if(dir == LEFT)
                    return P;
                else
                    if(P->parent == NULL) return nullptr;       // if root
                    N = P;
            }
            return N;
        }
        else {
            N = N->child[RIGHT];
            while(N->child[LEFT] != NULL)
                N = N->child[LEFT];
            return N;
        }
    }

    // TODO :: find previous node

    public:
    RBTIterator(node<Key, Value>* n = nullptr) {
        cur = n;
    }

    pair<Key, Value> get_value() {
        return this->cur->key_value;
    }

    node<Key, Value>* get_cur() {
        return this->cur;
    }


    RBTIterator operator ++ (int) {                     // postfix increment operator
        cur = next_node(cur);
        return *this;
    }

    bool operator != (const RBTIterator &iter) {
        return this->cur != iter.cur;
    }

    pair<Key, Value>* operator -> () {
        return &(this->cur->key_value);
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
        cout << "[" << N->key_value.first << "]";
        print_inorder(N->child[RIGHT]);
    }

    void print_level_order(node<Key, Value>* N) {
        cout << "[" << N->value << "]";
        queue<node<Key, Value>*> q;
        
    }

    public:

    typedef RBTIterator<Key, Value> iterator;

    iterator begin() {
        node<Key, Value> *n = root;
        while(n->child[LEFT] != NULL)
            n = n->child[LEFT];
        return iterator(n);
    }

    iterator end() {
        return iterator();                                 // end node is marked nullptr
    }

    /**
     * @brief 
     * 
     */
    iterator find(Key key) {
        return iterator(find_node(key));
    }

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
            if(key < N->key_value.first) {                          // if value is smaller than current node -> goto left child
                if(N->child[LEFT] == NULL) return N;
                else N = N->child[LEFT];
            }
            else if(key > N->key_value.first) {                     // if value is greater than current node -> goto right child
                if(N->child[RIGHT] == NULL) return N;           
                else N = N->child[RIGHT];
            }
            else {  // (key == N->key_value.first)
                cout << "key already exists" << endl;
                return NULL;
            }
        }
    }

    node<Key, Value>* find_node(Key key) {
        node<Key, Value> *N = root;
        while(N != NULL) {
            if(key < N->key_value.first) {
                N = N->child[LEFT];
            }
            else if(key > N->key_value.first) {
                N = N->child[RIGHT];
            }
            else {  // found key
                return N;
            }
        }
        return nullptr;
    }

    void insertion(pair<Key, Value> p) {
        node<Key, Value> *N = new node<Key, Value>(p);

        if(root == NULL) {                                  // if empty
            N->color = BLACK;
            root = N;
            return;
        }

        node<Key, Value> *P = find_parent_node(p.first);
        N->parent = P;
        int dir = (N->key_value.first < P->key_value.first)?LEFT:RIGHT;         // if the new node is smaller than Parent, dir is LEFT, else RIGHT
        P->child[dir] = N;                                  // add node as child of parent
        
        while(true) {
            if(P->color == BLACK) return;                       // if parent is black, is balanced
            // parent is RED
            node<Key, Value> *G = P->parent;                                // grand parent. If parent is RED, there must be non NULL G
            node<Key, Value> *U = (P->key_value.first < G->key_value.first)?G->child[RIGHT]:G->child[LEFT];
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


    node<Key, Value>* rotate(node<Key, Value>* P, node<Key, Value>* R, int dir) {

    }
    
    int find_child_dir(node<Key, Value>* N) {
        if(N->parent == NULL) return -1;        // is root
        if(N->parent->child[LEFT] == N) return LEFT;
        return RIGHT;
    }

    node<Key, Value>* standard_BST_deletion(node<Key, Value>* N) {
        // leaf node
        if(N->child[LEFT] == NULL && N->child[RIGHT] == NULL)
            

        // single child
        else if(V->child[LEFT] != NULL)


        // two children
        else


        return 
    }

    void deletion(Key key) {
        // 0. find the node to be deleted
        // set N and U. {N: node to delete, U: node that replaces V}

        // FIND N
        node<Key, Value>* N = find_node(key);
        if(N == nullptr) return;                                // key does not exist, nothing to do

        node<Key, Value>* P = N->parent;
        int dir = find_child_dir(N);
        node<Key, Value>* S = N->child[1-dir];
        
        N = standard_BST_deletion(N);
        
        
        // FIND U
        node<Key, Value> *U;
        // check if V is leaf node
        
        // find maximum in the left sub tree
        else if(V->child[LEFT] != NULL) {
            U = V->child[LEFT];
            while(U->child[RIGHT] != NULL)
                U = U->child[RIGHT];
        }
        // if no left child
        else
            U = V->child[RIGHT];

        // 1. Do standard BST deletion
        // 2. if either u or v is RED, mark the replaced child as BLACK and DONE.
        if(U != NULL && (V->color == RED || U->color == RED)) {
            V->key_value = U->key_value;
            V->color = BLACK;
            // int dir = find_child_dir(U);
            U->parent.
            delete U;
            return;
        }

        // standard BST delete
        if(U != NULL) // if U is not NULL


        // 3. if both u and v is BLACK (both u, v RED cannot exist if RBT is properly made)
        // 3.2 Let sibling of v be s
        int dir = (V->parent)
        node<Key, Value> *S = V->parent
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


// int main(int argc, char const *argv[])
// {
//     /* code */

//     RBT<string, int> rbt;
//     rbt.insertion(make_pair("ab", 10));
//     rbt.insertion(make_pair("b", 99));
//     rbt.insertion(make_pair("zz", 1));
//     rbt.insertion(make_pair("c", 0));
//     rbt.print();

//     return 0;
// }