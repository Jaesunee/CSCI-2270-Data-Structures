#include <iostream>
#include "SentenceReverser.hpp"

using namespace std;

SentenceReverser::SentenceReverser()
{
    stackHead = NULL;
}

SentenceReverser::~SentenceReverser()
{
    Word *current;
    while(!isEmpty())
    {
        current = stackHead;
        stackHead = stackHead->next;
        delete current;
    }
}

bool SentenceReverser::isEmpty()
{
	if(stackHead == NULL)
    {
        return true;
    }else{
        return false;
    }
}

void SentenceReverser::push(string word)
{
    
    Word *newHead = new Word();
    newHead->word = word;
    
    if(isEmpty()){
        stackHead = newHead;
        stackHead->next = NULL;
    }else{
        newHead->next = stackHead;
        stackHead = newHead;
    }
    
    newHead = NULL;
    delete newHead;
}

string SentenceReverser::pop()
{
    Word *oldHead;
    string pop;

    if(isEmpty()){
        oldHead = NULL;
        delete oldHead;
        cout << "Stack empty, cannot pop a word.";
        return "";
    }else{
        oldHead = stackHead;
        stackHead = stackHead->next;
        pop = oldHead->word;
        delete oldHead;
    }
    return pop;
}

Word* SentenceReverser::peek()
{
    if(isEmpty()){
        cout << "Stack empty, cannot peek." << endl;
        return stackHead;
    }else{
        return stackHead;
    }
}

void SentenceReverser::evaluate(string* s, int size)
{
    /*TODO: 1. Scan the array s from start
            2. Check for opening and closing brackets.
            3. Push each element on the stack till you encounter a "]"
            4. Then keep popping (& processing) from the stack till you get a "[".
            5. Handle the boundery cases as required.
            6. Read the writeup for more details. Another example is in Appendix 2.
    */

   int count = 0;

   for(int i = 0; i < size; i++)
   {
        if(s[i] == "]"){
            while(peek()->word != "["){
                cout << pop() << " ";
                count++;
            }
            pop();
            cout << "- " << count << endl;
            count = 0;
        }
        else
        {
            push(s[i]);
        } 
   }

   if(!isEmpty()){
       cout << "err: Invalid String";
   }
}
