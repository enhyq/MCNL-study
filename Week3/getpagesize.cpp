#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << getpagesize() << endl;
    return 0;
}
