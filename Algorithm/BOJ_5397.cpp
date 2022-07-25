/**
 * @author Eunhyeok Kwon
 * @date 2022-07-26 ~ !
 * @link https://www.acmicpc.net/problem/5397
 */

/*
 * When key logger log is given
 * extract password:
 *  backspace       -
 *  left arrow      <
 *  right arrow     >
 */

#include <iostream>

using namespace std;

struct node
{
    char letter;
    node* prev;
    node* next;

    node(char letter) {
        this->letter = letter;
        prev = NULL;
        next = NULL;
    }
    node(node* prev, char letter, node* next) {
        this->letter = letter;
        this->prev = prev;
        this->next = next;
    }
};

int main(int argc, char const *argv[])
{
    int T, i;
    node *top, *cur, *tmp;
    string str;
    char l;
    cin >> T;
    while(T--)
    {
        // free linked list
        top = NULL;
        cur = top;
        cin >> str;
        for(i=0; i<str.length(); i++)
        {
            l = str.at(i);
            if(('a'<=l && l <= 'z') || ('A'<=l && l<='Z'))
            {
                if(top == NULL)
                {
                    node *new_node = new node(l);
                    top = new_node;
                    cur = new_node;
                }
                else
                {
                    node *new_node = new node(cur, l, cur->next);
                    cur->next = new_node;
                    if(cur->next)
                    {
                        cur->next->prev = new_node;
                    }
                    cur = new_node;
                }
            }
            else if(top == NULL)
            {
                continue;
            }
            else
            {
                switch (l)
                {
                    case '<':
                        if(cur->prev != NULL)
                        {
                            cur = cur->prev;
                        }
                        break;
                    case '>':
                        if(cur->prev != NULL)
                        {
                            cur = cur->next;
                        }
                        break;
                    case '-':
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                        tmp = cur;
                        cur = cur->prev?cur->prev:cur->next;
                        // case when left end node
                        // when top is deleted
                        delete tmp;
                        
                        break;
                }
            }
        }
        
        while(top != NULL)
        {
            cout << top->letter;
            top = top->next;
        }
        cout << endl;

    }
    return 0;
}
