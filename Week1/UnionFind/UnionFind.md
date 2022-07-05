# Union Find

이름 그대로 union(합치기)와 find(찾기) 연산을 지원하는 자료구조

## What is "Disjoint Set"
* 서로 중복되지 않는 부분 집합
* no common element -> "상호 배타적 집합" -> "mutually exclusive"
* Union Find는 disjoint set을 표현할 때 사용되는 알고리즘이다


disjoint set을 구현하는데는 Tree가 가장 효율적이다
* 각 node가 parent를 가르키도록 해서 root를 확인 할 수 있으면
* 두집합을 비교할 때 모든 원소를 비교하는 것이 아니라 각 집합의 root만 비교하면 되기 때문에
* 합칠 때에서 한 집합의 root의 parent가 다른 집합의 root를 가르키도록 이거 하나만 변경해 주면 된다.

### 사용 예시
* Kruskal MST