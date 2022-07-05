# Red Black Tree
Is a type of *balanced* **binary search tree(BST)**

BST summary:
* "특정 key값에 대해서 삽입, 삭제, 탐색이 가능한 자료구조"
* left, smaller
* right, bigger


difference between AVL and RB tree?
> "the best ones are Red-Black Tree and AVL Tree. They both guarantee  𝑂(𝑙𝑜𝑔𝑁)  insertion, deletion and search. The main difference between them is that AVL is more strict in balancing, so it has slightly bigger constant factor in insertions and deletions than RB-Tree, but, due to this strict balance, searches are more fast. If you are doing few insertions/erasions and a lot of searches, AVL is better; If you are doing a lot of insertions/erasions and few searches, RB-Tree is better; Apart from this special cases, they are almost equal." -Quora

> "The AVL trees are more balanced compared to Red-Black Trees, but they may cause more rotations during insertion and deletion. So if your application involves frequent insertions and deletions, then Red-Black trees should be preferred. And if the insertions and deletions are less frequent and search is a more frequent operation, then AVL tree should be preferred over the Red-Black Tree." -GeeksforGeeks

* Some kind of transformation or rotation is needed after insertion or deletion to keep balanced state

## Red-Black Tree rules
* root is black
* leaf node is black
* red's child is black -> no two red in a row
* at all leaf node, black depth is same

There are two ways to rebalance the tree
* Restructuring 
* Rebalancing

* rebalancing can propagate up to the root at worst case


## Wikepedia data
* There are 6 cases for both insertion and deletion (total 12)...
