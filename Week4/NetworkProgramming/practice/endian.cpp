#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int a = 0;
    int *i = &a;
    char *c = (char*)&a;
    // c+=1;
    *c = 0x01;
    cout << *i << endl;

    return 0;
}
