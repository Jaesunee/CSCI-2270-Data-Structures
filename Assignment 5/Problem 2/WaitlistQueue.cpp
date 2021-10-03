#include "WaitlistQueue.hpp"

using namespace std;

// COMPLETE THE FUNCTIONS BELOW
int items; 

WaitlistQueue::WaitlistQueue(int qSize)
{
    qFront = -1;
    qEnd = -1;

    qCapacity = qSize;
    queue = new string[qSize];
}

WaitlistQueue::~WaitlistQueue()
{
    delete [] queue;
    queue = NULL;
}

void WaitlistQueue::enqueue(std::string value)
{
    
    if(!isFull()){
        if(qFront == -1 && qEnd == -1){
            qFront++;
            qEnd++;
            queue[qFront] = value;
            items++;
        }else if(qEnd == qCapacity-1){
            qEnd = 0;
            queue[qEnd] = value;
            items++;
        }else{
            queue[qEnd+1] = value;
            qEnd++;  
            items++;
        }
    }else{
        cout<< "Waitlist is full. Cannot enqueue." << endl;
    }
}

void WaitlistQueue::dequeue()
{
    if(!isEmpty()){
        if(qFront == qEnd){
            items--;
            qFront = -1;
            qEnd = -1;
        }else if(qFront == qCapacity-1){
            qFront = 0;
            items--;
        }else{
            items--;
            //queue[qFront] = nullptr;
            qFront++;
        }
    }else {
        cout << "Wailist is empty. Cannot dequeue." << endl;
    }
}

std::string WaitlistQueue::peek()
{
    string element;
    if (isEmpty()){
        return "<EMPTY QUEUE>";
    }else{
        element = queue[qFront];
        return element;
    }
}

void WaitlistQueue::resize(int newSize)
{
    string* newQueue = new string[newSize];
    
    int index = 0;
    int index2 = 0;
    
    
    
    if (qFront > qEnd){
        
        while(qFront < qCapacity){
            if(index < newSize-1){
                newQueue[index] = queue[qFront];
                index++;
                qFront++;
            }else{
                break;
            }
        }

        while(index2 < qEnd){
            if(index < newSize -1){
                newQueue[index] = queue[index2];
                index2++;
                index++;
            }else{
                break;
            }
        }
        newQueue[index] = queue[index2];
        qFront = 0;
        qEnd = index;
    }else{
        while(index < newSize-1){
            while(qFront < qEnd){
                newQueue[index] = queue[qFront];
                qFront++;
                index++;
            }
            newQueue[index] = queue[qFront];
            break;
        }
        qFront = 0;
        qEnd = index;
    }
    delete[] queue;
    qCapacity = newSize;
    queue = newQueue;
    newQueue = NULL;
    delete newQueue;
}

int WaitlistQueue::size()
{
    return items;
}

int WaitlistQueue::capacity()
{
    return qCapacity;
}

bool WaitlistQueue::isEmpty()
{
    if(qFront == -1 && qEnd == -1){
        return true;
    }
    return false;
}

bool WaitlistQueue::isFull()
{
    if((qEnd == qCapacity-1 && qFront == 0) || (qEnd == qFront - 1)){
        return true;
    }

    return false;
}
