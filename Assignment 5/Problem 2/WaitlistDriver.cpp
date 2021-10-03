
#include <iostream>
#include <string>
#include "WaitlistQueue.hpp"

using namespace std;

int main(int argc, char* argv[]) 
{
    int capacity = stoi(argv[1]);

    cout << "Initial queue capacity = " << capacity << endl;

    WaitlistQueue q(capacity);

    bool isRunning = true;
    string command;
    string value;

    while (isRunning){
        cout << "#> ";
        cin >> command;
        
        if(command == "enqueue"){
            cin >> value;
            q.enqueue(value);
            q.printInfo();
        }else if(command == "dequeue"){
            q.dequeue();
            q.printInfo();
        }else if(command == "peek"){
            cout << q.peek() << endl;
            q.printInfo();
        }else if(command == "resize"){
            cin >> value;
            q.resize(stoi(value));
            cout << "Resizing from "<< capacity << " to " << value << endl;
            q.printInfo();
        }else if(command == "quit"){
            q.printInfo();
            cout << "Contents of the queue:" <<  endl;
            while(q.peek() != "<EMPTY QUEUE>"){
                 cout << q.peek() << " ";
                 q.dequeue();
            }
            isRunning = false;
        }else{
            isRunning = false;
        }
    }

    q.~WaitlistQueue();
    return 0;
}