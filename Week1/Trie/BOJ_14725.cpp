/**
 * @file BOJ_14725.cpp
 * @author Eunhyeok Kwon
 * @date 2022-07-05 ~ 
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * 개미는 내려가기만 할 수 있다.
 * 각 층은 "--"로 구분
 * 같은 층에 여러방 -> 사전 순서 먼저 (ex A before Z)
 * 개미굴의 구조를 그려라
 * 
 * 1 | N: 먹이의 정보 개수 (1 ≤ N ≤ 1000)
 * 2 ~ N+1 | 로봇 개미 한마리가 보내준 먹이 정보 개수 K + 먹이 String (1 ≤ K ≤ 15)
 * 
 * 전략:
 * 입력의 크기가 그렇게 크지 않기(?) 때문에(?) 일반적인 Trie를 사용해도 괜찮을 것 같다
 * Trie에 순서대로 먹이 문자열 들을 집어 넣는다
 * Recursive하게 print하는 함수를 만들어서 출력하고, 각 층마다 "--"를 추가
 */

#define SIZE 1000

typedef struct node
{
    /* data */
    string food;
    node* children[SIZE];
};


class Trie {
    private:
    node* root;

    public:
    Trie() {
        root = new node();
        
    }
};

int main(int argc, char const *argv[])
{
    // for faster input and output
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    

    return 0;
}
