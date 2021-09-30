#include <iostream>
#include "StackLL.hpp"

using namespace std;

StackLL::StackLL()
{
    stackHead = nullptr;
}

StackLL::~StackLL()
{
    while(!isEmpty())
        pop();
}

bool StackLL::isEmpty()
{
    return (stackHead == nullptr);
}

void StackLL::push(char key)
{
    Node* nn = new Node;
    nn->key = key;
    nn->next = nullptr;
    nn->next = stackHead;
    stackHead = nn;
}

void StackLL::pop()
{
    //TODO
    //Write the condition to check stack underflow
    if (isEmpty()){
        cout << "stack underflow";

    }else{
        Node* temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
}

char StackLL::peek()
{
    if(!isEmpty()){
        return stackHead->key;
    }
        
    else{
        cout<<"empty stack. can not peek"<<endl;
        return -1;
    }
}
