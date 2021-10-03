#pragma once
#include <iostream>
#include <string>
#include <exception>

class WaitlistQueue {

    private:
        std::string* queue;                 // the array container
        int qCapacity;                      // the size of the array
        int qFront;                         // queueFront's index
        int qEnd;                           // qEnd's index

    public:
        WaitlistQueue(int qSize=10);        // parameterized constructor
        ~WaitlistQueue();                   // destructor

        void enqueue(std::string value);    // add a value to the queue 
        void dequeue();                     // remove a value from the queue
        std::string peek();                 // get a value from the queue

        void resize(int new_size);          // resize the queue container
        int size();                         // get the number of elements in the queue
        int capacity();                     // the total size of the queue container
        bool isEmpty();                     // return whether the queue is empty
        bool isFull();                      // return whether the queue is full

        // Helper function for debugging and monitoring the queue
        void printInfo() {
            std::cout << "peek()=" << peek() << ", "
                      << "qFront=" << qFront << ", "
                      << "qEnd=" << qEnd << std::endl;
        }
};