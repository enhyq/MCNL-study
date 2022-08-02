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
    node *prev;
    node *next;

    node(char letter)
    {
        this->letter = letter;
        prev = NULL;
        next = NULL;
    }
    node(node *prev, char letter, node *next)
    {
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
    while (T--)
    {
        // free linked list

        top = new node(0); // top begins with empty node that stores 0 as its letter value, this node is always the top node
        cur = top;
        cin >> str;
        for (i = 0; i < str.length(); i++)
        {
            l = str.at(i);
            if (('a' <= l && l <= 'z') || ('A' <= l && l <= 'Z') || ('0' <= l && l <= '9'))
            {
                // new node is inserted after the current node
                // cur - new_node - cur->next
                node *new_node = new node(cur, l, cur->next);
                if (cur->next)
                    cur->next->prev = new_node;
                cur->next = new_node;
                cur = new_node;
            }
            else if (cur != top)
            {
                if (l == '<')
                {
                    if (cur->prev != NULL)
                        cur = cur->prev;
                }
                else if (l == '-')
                {
                    if (cur->prev)
                        cur->prev->next = cur->next;
                    if (cur->next)
                        cur->next->prev = cur->prev;
                    tmp = cur; // node to delete
                    cur = cur->prev;
                    delete tmp;
                }
                else if (l == '>')
                {
                    if (cur->next != NULL)
                        cur = cur->next;
                }
            }
            else
            {
                if (l == '>')
                {
                    if (cur->next != NULL)
                        cur = cur->next;
                }
            }

            // tmp = top;
            // while (tmp != NULL)
            // {
            //     cout << (char)tmp->letter;
            //     if(tmp == cur) cout << "|";
            //     tmp = tmp->next;
            // }
            // cout << endl;
        }

        while (top != NULL)
        {
            cout << (char)top->letter;
            top = top->next;
        }
        cout << endl;
    }
    return 0;
}
