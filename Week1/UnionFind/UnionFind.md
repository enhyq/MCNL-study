# Union Find

* 이름 그대로 union(합치기)와 find(찾기) 연산을 지원하는 자료구조
* "여러개의 노드가 존재할 때 두개의 노드를 선택해서, 현재 이 두 노드가 서로 같은 그래프에 속하는지 판별하는 알고리즘"


## What is "Disjoint Set"
* 서로 중복되지 않는 부분 집합
* no common element -> "상호 배타적 집합" -> "mutually exclusive"
* Union Find는 disjoint set을 표현할 때 사용되는 알고리즘이다


disjoint set을 구현하는데는 **Tree**가 가장 효율적이다
* 각 node가 parent를 가르키도록 해서 root를 확인 할 수 있으면
* 두집합을 비교할 때 모든 원소를 비교하는 것이 아니라 각 집합의 root만 비교하면 되기 때문에
* 합칠 때에서 한 집합의 root의 parent가 다른 집합의 root를 가르키도록 이거 하나만 변경해 주면 된다.
* root는 자기 자신을 가리키게 하면 된다.
* 경우에 따라서 Union operation을 수행 할 때 value의 값을 비교해서 더 작은 값을 가진 node가 큰 값을 가진 node의 parent가 되도록 해야 할 때도 있다. (ex: Kruskal MST) 

근데 Tree라고 해서 별 다른게 아니라 평소에 만들던 Node Array이다. (각 node에 value를 담는 변수와 parent를 가리키는 포인터가 있다.)

### 사용 예시
* Kruskal MST
