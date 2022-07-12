#include <iostream>
#include <queue>

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

// 
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

template <typename Key, typename Value>
class RBT {
    private:
    node *root;

    // prints element in inorder traversal (recursive)
    void print_inorder(node* N) {
        if(N == NULL) return;
        
        print_inorder(N->child[LEFT]);
        cout << "[" << N->value << "]";
        print_inorder(N->child[RIGHT]);
    }

    void print_level(node* N) {
        
    }

    public:
    // Constructs a new RBT object with NULL root
    RBT() {
        root = NULL;
    }

    node* find_parent(int value) {
        node *N = root;
        if(N == NULL) return NULL;                          // empty, no parent
        while(true) {
            if(value < N->value) {                          // if value is smaller than current node -> goto left child
                if(N->child[LEFT] == NULL) return N;
                else N = N->child[LEFT];
            }
            else if(value > N->value) {                     // if value is greater than current node -> goto right child
                if(N->child[RIGHT] == NULL) return N;           
                else N = N->child[RIGHT];
            }
            // didn't implement case when (value == N->value)
        }
    }

    void insertion(Key key, Value value) {
        node *N = new node(key, value);

        if(root == NULL) {                                  // if empty
            N->color = BLACK;
            root = N;
            return;
        }

        node *P = find_parent(key, value);
        N->parent = P;
        int dir = (N->value < P->value)?LEFT:RIGHT;         // if the new node is smaller than Parent, dir is LEFT, else RIGHT
        P->child[dir] = N;                                  // add node as child of parent
        
        while(true) {
            if(P->color == BLACK) return;                       // if parent is black, is balanced
            // parent is RED
            node *G = P->parent;                                // grand parent. If parent is RED, there must be non NULL G
            node *U = (P->value < G->value)?G->child[RIGHT]:G->child[LEFT];
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

    }

    void print() {
        cout << "print: ";
        print_inorder(root);
        cout << endl;
    }

};

int main(int argc, char const *argv[])
{
    /* code */

    RBT rbt;
    for(int i=100; i>0; i-=2) {
        rbt.insertion(i);
        // rbt.print();
    }
    for(int i=1; i<100; i+=2) {
        rbt.insertion(i);
        // rbt.print();
    }
    rbt.print();

    return 0;
}
