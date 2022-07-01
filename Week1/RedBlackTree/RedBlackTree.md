# Red Black Tree
Is a type of balanced binary search tree

difference between AVL and RB tree?
> "the best ones are Red-Black Tree and AVL Tree. They both guarantee  𝑂(𝑙𝑜𝑔𝑁)  insertion, deletion and search. The main difference between them is that AVL is more strict in balancing, so it has slightly bigger constant factor in insertions and deletions than RB-Tree, but, due to his strict balance, searches are more fast. If you are doing few insertions/erasions and a lot of searches, AVL is better; If you are doing a lot of insertions/erasions and few searches, RB-Tree is better; Apart from this special cases, they are almost equal." -Quora

* Some kind of transformation or rotation is needed after insertion or deletion to keep balanced state

* 