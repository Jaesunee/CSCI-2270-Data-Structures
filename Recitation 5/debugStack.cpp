#include <iostream>
#include "StackLL.hpp"
using namespace std;

int main()
{
    StackLL stack;
    stack.push('1');
    stack.push('2');
    stack.push('3');

    for(int i=0; i<4; i++)
        stack.pop();
    return 0;
}

