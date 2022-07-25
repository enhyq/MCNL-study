/**
 * @author Eunhyeok Kwon
 * @date 2022-07-25 ~ 2022-07-25
 * @link https://www.acmicpc.net/problem/10828
 */

/*
 * Problem description
 * Create a stack that can store integer values with 5 functionalities:
 *  push X
 *  pop
 *  size
 *  empty
 *  top
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int stack[10000], top=-1;

    int N, num;
    string cmd;
    for(cin >> N; N>0; N--)
    {
        cin >> cmd;
        if(cmd == "push")
        {
            cin >> num;
            stack[++top] = num;
        }
        else if(cmd == "pop")
        {
            if(top == -1)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << stack[top--] << endl;
            }
        }
        else if(cmd == "size")
        {
            cout << top+1 << endl;
        }
        else if(cmd == "empty")
        {
            cout << (top == -1) << endl;
        }
        else if(cmd == "top")
        {
            if(top == -1)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << stack[top] << endl;
            }
        }
        else
        {
            cout << "unknown command" << endl;
        }
    }
    

    return 0;
}
