/****************************************************************/
/*                Sentence Reverser Class Implementation        */
/****************************************************************/
/*            LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING!    */
/****************************************************************/

#pragma once
#include <iostream>

struct Word
{
    std::string word;
    Word* next;
};

class SentenceReverser
{
private:
  Word* stackHead; // pointer to the top of the stack

public:
  SentenceReverser();
  ~SentenceReverser();
  bool isEmpty();
  void push(std::string word);
  std::string pop();
  Word* peek();
  void evaluate(std::string* s, int size);
};
