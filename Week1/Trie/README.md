# Trie
Trie is also known as "digital tree" or "prefix tree"

A type of k-ary search tree

It's most often used for string search

Invented in 1960 by **Edward Fredkin**, **Axel Thue**, and **René de la Briandais**

Also used in NLP(Natural Language Processing)

The term trie came from "retrieval"

> "All the children of a node have a common prefix of the string associated with that parent node, and the root is associated with the empty string. This task of storing data accessible by its prefix can be accomplished in a memory-optimized way by employing a radix tree." - Wikepedia

parent node는 empty string을 나타낸다.  
단어가 많고 다양해 질 수록 결국에는 (영어만 따졌을 때) 1st level child의 개수는 alphabet의 개수인 26개가 될 것이다.  
다만 처음부터 공간을 다 할당해서 시작하는 것은 common prefix를 가지고 있는 아주 긴 단어들을 조금 저장 할 때 메모리 낭비가 심하기 때문에 단어를 추가하면서 필요한 element를 추가하는 방식으로 만들어야 한다.

radix tree?
> "radix tree (also radix trie or compact prefix tree) is a data structure that represents a space-optimized trie (prefix tree) in which each node that is the only child is merged with its parent." - Wikepedia

그냥 node가 더 짧아진 구현 방법이다  

근데 예를 들어 Avenger 와 Avengers 단어 2개가 있을 때  
only child는 parent와 합쳐지기 때문에 Avengers만 생기게 되는데  
s 가 없는 Avenger 단어는 어떻게 검색하는 걸까?

only child 이지만 독립적인 단어가 되는 경우를 알려주는 변수를 하나 추가해서, 독립적인 단어가 되면 합치지 않도록 하면 될까?

그렇다

> "If the input key is a prefix of the existing key in Trie, we simply mark the last node of the key as the end of a word. The key length determines Trie depth." - GeeksforGeeks

## Implementation
일단은 linked list를 사용해서 각 insert 마다 필요한 만큼 append하려고 했는데.. 단어가 다양해 질 수록 linked list보다는 array가 memory efficient하다. 둘의 장점을 둘다 가져오는 방식이 없을까? 

linked list는 자신의 value, 그리고 link 2개로 구성되기 때문에 common prefix의 개수가 13개 보다 적다면 linked list가 유리하고 그 이후에는 array가 memory efficient하다고 생각했는데.. 그렇게 간단하지만은 않은 것 같다

처음에는 일단 array로 구현해보자

### insertion

word의 각 letter를 iterate하면서 존재하면 따라가고 존재하지 않으면 생성한후 따라간다
마지막 letter의 node에 독립적인 단어를 나타내는 변수를 마킹해준다

insertion에서 letter가 이미 존재하는지 존재하지 않는지 확인하는 더 빠른 방법이 일을까? -> hash table?? 


### search
array로 구현되어 있다면 search할 단어의 각 letter를 iterate하면서 해당 letter의 index 위치의 link가 null인지 또는 child가 있는지 확인하면 될 것이다  
* null을 만나면 false를 return하고  
* 마지막 letter까지 iterate했을 때 node에 독립 단어를 나타내는 마킹이 있으면 true, 없으면 false를 반환하면 될 것이다.

### deletetion
삭제는 귀찮다면..(?) 그냥 독립 단어 마킹만 false로 해주면 될 것이다.

하지만 메모리를 효율적으로 관리해야 한다면..

삭제를 하고 따라 올라오면서 a-z까지의 array의 모든 node들이 null인 경우 해당 array를 free시키면 될 것 같다.


### {variables}
구현을 하는데 필요한 변수들은 
root
characterValue struct

위 struct를 배열 형식으로 사용하려면 크기를 미리 26으로 맞추고 하면 되고 아니면 linked list 형태로 사용하면 될 것 같다

linked list 형태를 사용한다고 하면 int 순서나 알파벳 순서로 link를 걸어 놓는 것도 좋을 방법인듯 하다


### Questions
* do the nodes in Trie needs to be alphabetically sorted?
* yes

Trie는 linked list로 구현할 수 없다.
Indexing이 가능한 구조를 사용해야 한다.

-> linked list로 된 배열?
A - B - C - D - ...
입력된 알파벳의 index만큼 next link로 이동...
그럼 차라리 배열을 쓰지..

결론: array 사용해야됨