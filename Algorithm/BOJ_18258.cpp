    /**
     * @author Eunhyeok Kwon
     * @date 2022-08-01 ~ 2022-08-02
     * @link https://www.acmicpc.net/problem/18258
     */

    #include <iostream>
    #include <string.h>

    #define MAX_SIZE 2000001

    using namespace std;

    /*
    * make Queue with 6 functionalities
    *  push X
    *  pop
    *  size
    *  empty
    *  front
    *  back
    *
    * 명령의 수 N (1 ≤ N ≤ 2,000,000)
    * 제한시간: 1초
    *
    */

    class Queue
    {
    private:
        int *aa;
        // int aa[MAX_SIZE];
        // above command did not work
        // https://stackoverflow.com/questions/16123842/c-program-stops-working-when-the-array-size-is-too-large
        // this answer says that stack space might have run out
        int front, back;

    public:
        // Constructor
        Queue()
        {
            front = back = 0;
            aa = new int[MAX_SIZE];
        }

        bool Empty()
        {
            if(front == back)
                return true;
            return false;
        }

        int Size()
        {
            return back - front;
        }

        int Front()
        {
            if(Empty()) return -1;
            return aa[front];
        }

        int Back()
        {
            if(Empty()) return -1;
            return aa[back-1];
        }

        int Pop()
        {
            if(Empty()) return -1;
            return aa[front++];
        }

        void Push(int num)
        {
            // Doesn't check if array is full
            aa[back++] = num;
        }
        
    };

    main(int argc, char const *argv[])
    {
        ios_base :: sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int N, num;
        string cmd;
        Queue q;

        // cout << "started" << endl;

        cin >> N;

        // cout << "Will process " << N << " commands" << endl;

        while (N--)
        {
            cin >> cmd;
            if (cmd == "push")
            {
                cin >> num;
                q.Push(num);
            }
            else if (cmd == "pop")
            {
                cout << q.Pop() << "\n";
            }
            else if (cmd == "size")
            {
                cout << q.Size() << "\n";
            }
            else if (cmd == "empty")
            {
                cout << q.Empty() << "\n";
            }
            else if (cmd == "front")
            {
                cout << q.Front() << "\n";
            }
            else if (cmd == "back")
            {
                cout << q.Back() << "\n";
            }
        }

        return 0;
    }
