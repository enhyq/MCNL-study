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

enum
{
    BLACK,
    RED
};
enum
{
    LEFT,
    RIGHT
};

/**
 * @brief node structure used as an element in Red Black Tree
 *
 * @tparam Key
 * @tparam Value
 */
template <typename Key, typename Value>
struct node
{

    bool color;
    pair<Key, Value> key_value;
    node *parent;
    node *child[2];

    /**
     * @brief Construct a new node object with value
     */
    node(pair<Key, Value> key_value)
    {
        color = RED;
        this->key_value = key_value;
        parent = child[0] = child[1] = NULL; // parent is also initially NULL
    }
};

template <typename Key, typename Value>
class RBTIterator
{
private:
    node<Key, Value> *cur;

    /**
     * @brief Using inorder traversal, it finds and returns the next node
     *
     * @param N node to begin searching
     * @return node<Key, Value>*
     */
    node<Key, Value> *next_node(node<Key, Value> *N)
    {
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
        node<Key, Value> *P;
        if (N->child[RIGHT] == NULL)
        {
            while (N->parent != NULL)
            {
                P = N->parent;
                dir = (P->child[LEFT] == N) ? LEFT : RIGHT;
                if (dir == LEFT)
                    return P;
                else if (P->parent == NULL)
                    return nullptr; // if root
                N = P;
            }
            return N;
        }
        else
        {
            N = N->child[RIGHT];
            while (N->child[LEFT] != NULL)
                N = N->child[LEFT];
            return N;
        }
    }

    // TODO :: find previous node

public:
    RBTIterator(node<Key, Value> *n = nullptr)
    {
        cur = n;
    }

    pair<Key, Value> get_value()
    {
        return this->cur->key_value;
    }

    node<Key, Value> *get_cur()
    {
        return this->cur;
    }

    RBTIterator operator++(int)
    { // postfix increment operator
        cur = next_node(cur);
        return *this;
    }

    bool operator!=(const RBTIterator &iter)
    {
        return this->cur != iter.cur;
    }

    pair<Key, Value> *operator->()
    {
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
class RBT
{
private:
    node<Key, Value> *root;

    // prints element in inorder traversal (recursive)
    void print_inorder(node<Key, Value> *N)
    {
        if (N == NULL)
            return;

        print_inorder(N->child[LEFT]);
        cout << "[" << N->key_value.first << "]";
        print_inorder(N->child[RIGHT]);
    }

    void print_level_order(node<Key, Value> *N)
    {
        cout << "[" << N->value << "]";
        queue<node<Key, Value> *> q;
    }

public:
    typedef RBTIterator<Key, Value> iterator;

    iterator begin()
    {
        node<Key, Value> *n = root;
        while (n->child[LEFT] != NULL)
            n = n->child[LEFT];
        return iterator(n);
    }

    iterator end()
    {
        return iterator(); // end node is marked nullptr
    }

    /**
     * @brief
     *
     */
    iterator find(Key key)
    {
        return iterator(find_node(key));
    }

    // Constructs a new RBT object with NULL root
    RBT()
    {
        root = NULL;
    }

    /**
     * @brief comparing the keys, it finds the node that is to be the parent of the inserted new node
     *
     * @param key
     * @return node*
     */
    node<Key, Value> *find_parent_node(Key key)
    {
        node<Key, Value> *N = root;
        if (N == NULL)
            return NULL; // empty, no parent
        while (true)
        {
            if (key < N->key_value.first)
            { // if value is smaller than current node -> goto left child
                if (N->child[LEFT] == NULL)
                    return N;
                else
                    N = N->child[LEFT];
            }
            else if (key > N->key_value.first)
            { // if value is greater than current node -> goto right child
                if (N->child[RIGHT] == NULL)
                    return N;
                else
                    N = N->child[RIGHT];
            }
            else
            { // (key == N->key_value.first)
                cout << "key already exists" << endl;
                return NULL;
            }
        }
    }

    node<Key, Value> *find_node(Key key)
    {
        node<Key, Value> *N = root;
        while (N != NULL)
        {
            if (key < N->key_value.first)
            {
                N = N->child[LEFT];
            }
            else if (key > N->key_value.first)
            {
                N = N->child[RIGHT];
            }
            else
            { // found key
                return N;
            }
        }
        return nullptr;
    }

    void insertion(pair<Key, Value> p)
    {
        node<Key, Value> *N = new node<Key, Value>(p);

        if (root == NULL)
        { // if empty
            N->color = BLACK;
            root = N;
            return;
        }

        node<Key, Value> *P = find_parent_node(p.first);
        N->parent = P;
        int dir = (N->key_value.first < P->key_value.first) ? LEFT : RIGHT; // if the new node is smaller than Parent, dir is LEFT, else RIGHT
        P->child[dir] = N;                                                  // add node as child of parent

        while (true)
        {
            if (P->color == BLACK)
                return; // if parent is black, is balanced
            // parent is RED
            node<Key, Value> *G = P->parent; // grand parent. If parent is RED, there must be non NULL G
            node<Key, Value> *U = (P->key_value.first < G->key_value.first) ? G->child[RIGHT] : G->child[LEFT];
            // If U is BLACK or NIL
            if (U == NULL || U->color == BLACK)
            {
                if (G->child[dir] != P)
                { // if inner node
                    G->child[1 - dir] = N;
                    N->child[1 - dir] = P;
                    P->child[dir] = NULL;
                    dir = 1 - dir;
                    P = N;
                    N = P->child[dir];
                }
                G->child[dir] = P->child[1 - dir];
                if (G->child[dir] != NULL)
                    G->child[dir]->parent = G;

                if (G == root)
                    root = P;
                else
                    G->parent->child[dir] = P;
                P->parent = G->parent;

                P->child[1 - dir] = G;
                G->parent = P;

                P->color = BLACK;
                G->color = RED;
                return; // BREAK after restructuing, it's balanced
            }
            // If U is RED                                      // do recoloring
            else
            {
                P->color = U->color = BLACK;
                G->color = RED;
                N = G; // repeat the process
                if (N->parent == NULL)
                {
                    // N == root
                    if (N->color == RED)
                        N->color = BLACK;
                    break;
                }
                // N parent is NULL when N is root
                P = N->parent;
            }
        }
    }

    // rotate P and R in dir direction
    node<Key, Value> *rotate(node<Key, Value> *P, node<Key, Value> *R, int dir)
    {
    }

    int find_child_dir(node<Key, Value> *N)
    {
        if (N->parent == NULL)
            return -1; // is root
        if (N->parent->child[LEFT] == N)
            return LEFT;
        return RIGHT;
    }

    node<Key, Value> *standard_BST_deletion(node<Key, Value> *N)
    {
        // leaf node
        if (N->child[LEFT] == NULL && N->child[RIGHT] == NULL)
            return NULL;
        // single child
        else if (N->child[LEFT] != NULL) // in RBT, single child cannot have sub child, due to balance issue
            return N->child[RIGHT];
        // two children
        else
            N = N->child[LEFT];
        while (N->child[RIGHT] != NULL)
            N = N->child[RIGHT]; // find max in the left sub tree
        return N;
    }

    void myDeletion(Key key)
    {
        // 0. find the node to be deleted and delete
        // N: node to be deleted
        // U: node to replace deleted N

        // FIND N
        node<Key, Value> *N = find_node(key); // find node to be deleted
        if (N == nullptr)
            return; // key does not exist, nothing to do

        node<Key, Value> *U = standard_BST_deletion(N); // node that will replace delete N

        // 1. Do standard BST deletion
        // place of U is important, but after getting P and S, U is not very important
        node<Key, Value> *P; // parent of deleted node
        node<Key, Value> *S; // sibling of deleted node
        int dir;
        if (U == NULL)
        { // if node to delete was leaf node
            if (N == root)
            { // if node to delete was root -> root is not NULL and RBT is empty
                root = NULL;
                delete N;
                return;
            }
            P = N->parent;
            dir = find_child_dir(N);
            S = P->child[1 - dir];
        }
        else
        {
        }

        // 2. if either u or v is RED, mark the replaced child as BLACK and DONE.
        if (U != NULL && (N->color == RED || U->color == RED))
        {
            N->key_value = U->key_value;
            N->color = BLACK;
            // int dir = find_child_dir(U);
            // U->parent.
            delete U;
            return;
        }

        // standard BST delete
        if (U != NULL) // if U is not NULL

            // 3. if both u and v are BLACK (both u, v RED cannot exist if RBT is properly made)
            // 3.2 Let sibling of v be s
            int dir = (N->parent);
        node<Key, Value> *S = N->parent;
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

    void print()
    {
        cout << "inorder print: ";
        print_inorder(root);
        cout << endl;
    }

    /************************************************************************/

    // returns pointer to uncle
    node<Key, Value> *uncle()
    {
        // If no parent or grandparent, then no uncle
        if (parent == NULL or parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right;
        else
            // uncle on left
            return parent->parent->left;
    }

    // check if node is left child of parent
    bool isOnLeft() { return this == parent->left; }

    // returns pointer to sibling
    node<Key, Value> *sibling()
    {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    // moves node down and moves given node in its place
    void moveDown(node<Key, Value> *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild()
    {
        return (left != NULL and left->color == RED) or
               (right != NULL and right->color == RED);
    }

    // left rotates the given node
    void leftRotate(node<Key, Value> *x)
    {
        // new parent will be node's right child
        node<Key, Value> *nParent = x->right;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right = nParent->left;
        // connect new parent's left element with node
        // if it is not null
        if (nParent->left != NULL)
            nParent->left->parent = x;

        // connect new parent with x
        nParent->left = x;
    }

    void rightRotate(node<Key, Value> *x)
    {
        // new parent will be node's left child
        node<Key, Value> *nParent = x->left;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left = nParent->right;
        // connect new parent's right element with node
        // if it is not null
        if (nParent->right != NULL)
            nParent->right->parent = x;

        // connect new parent with x
        nParent->right = x;
    }

    void swapColors(node<Key, Value> *x1, node<Key, Value> *x2)
    {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(node<Key, Value> *u, node<Key, Value> *v)
    {
        int temp;
        temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    // fix red red at given node
    void fixRedRed(node<Key, Value> *x)
    {
        // if x is root color it black and return
        if (x == root)
        {
            x->color = BLACK;
            return;
        }

        // initialize parent, grandparent, uncle
        Node *parent = x->parent, *grandparent = parent->parent,
             *uncle = x->uncle();

        if (parent->color != BLACK)
        {
            if (uncle != NULL && uncle->color == RED)
            {
                // uncle red, perform recoloring and recurse
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            }
            else
            {
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                    {
                        // for left right
                        swapColors(parent, grandparent);
                    }
                    else
                    {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else
                    {
                        swapColors(parent, grandparent);
                    }

                    // for right right and right left
                    leftRotate(grandparent);
                }
            }
        }
    }

    // find node that do not have a left child
    // in the subtree of the given node
    node<Key, Value> *successor(node<Key, Value> *x)
    {
        node<Key, Value> *temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    node<Key, Value> *BSTreplace(node<Key, Value> *x)
    {
        // when node have 2 children
        if (x->left != NULL and x->right != NULL)
            return successor(x->right);

        // when leaf
        if (x->left == NULL and x->right == NULL)
            return NULL;

        // when single child
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }

    // deletes the given node
    void deleteNode(node<Key, Value> *v)
    {
        node<Key, Value> *u = BSTreplace(v);

        // True when u and v are both black
        bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
        node<Key, Value> *parent = v->parent;

        if (u == NULL)
        {
            // u is NULL therefore v is leaf
            if (v == root)
            {
                // v is root, making root null
                root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    // u and v both black
                    // v is leaf, fix double black at v
                    fixDoubleBlack(v);
                }
                else
                {
                    // u or v is red
                    if (v->sibling() != NULL)
                        // sibling is not null, make it red"
                        v->sibling()->color = RED;
                }

                // delete v from the tree
                if (v->isOnLeft())
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL or v->right == NULL)
        {
            // v has 1 child
            if (v == root)
            {
                // v is root, assign the value of u to v, and delete u
                v->val = u->val;
                v->left = v->right = NULL;
                delete u;
            }
            else
            {
                // Detach v from tree and move u up
                if (v->isOnLeft())
                {
                    parent->left = u;
                }
                else
                {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                }
                else
                {
                    // u or v red, color u black
                    u->color = BLACK;
                }
            }
            return;
        }

        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(node<Key, Value> *x)
    {
        if (x == root)
            // Reached root
            return;

        node<Key, Value> *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)
        {
            // No sibiling, double black pushed up
            fixDoubleBlack(parent);
        }
        else
        {
            if (sibling->color == RED)
            {
                // Sibling red
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft())
                {
                    // left case
                    rightRotate(parent);
                }
                else
                {
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {
                // Sibling black
                if (sibling->hasRedChild())
                {
                    // at least 1 red children
                    if (sibling->left != NULL and sibling->left->color == RED)
                    {
                        if (sibling->isOnLeft())
                        {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else
                {
                    // 2 black children
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }

    /************************************************************************/
};

int main(int argc, char const *argv[])
{
    /* code */

    RBT<string, int> rbt;
    rbt.insertion(make_pair("ab", 10));
    rbt.insertion(make_pair("b", 99));
    rbt.insertion(make_pair("zz", 1));
    rbt.insertion(make_pair("c", 0));
    rbt.print();

    return 0;
}