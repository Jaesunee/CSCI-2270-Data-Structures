
#include <iostream>
#include <string>
#include "WaitlistQueue.hpp"

using namespace std;

int main(int argc, char* argv[]) 
{
    cout << boolalpha;  // this displays boolean values as true and false


    WaitlistQueue q(5);

    q.enqueue("buff_24");
    cout << q.peek() << endl;

    q.enqueue("buff_25");
    q.enqueue("buff_26");
    q.printInfo();

    q.dequeue();
    q.dequeue();
    q.printInfo();

    // Another sample run below:
/*
    WaitlistQueue q(5);

    q.enqueue("buff_24");
    q.enqueue("buff_25");
    q.enqueue("buff_26");
    q.printInfo();

    q.dequeue();
    q.dequeue();
    q.printInfo();

    q.dequeue();
    q.printInfo();
*/

    return 0;
}