#include "LinkedList.h"

using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = new Node;
    head->key = newKey;
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }

  else{

      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }


// TODO: SILVER PROBLEM
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n)
{
  bool isDeleted = false;

  if(head == NULL){
    cout<< "List is already empty"<<endl;
    return isDeleted;
  }

  // Special case to delete the head
    if (n == 0) {
      Node *temp = head;
      head = head->next;
      delete temp;
      isDeleted = true; 
      return isDeleted;
    }

  Node *pres = head;
	Node *prev = NULL;


  //iterate through nodes until you reach certain node and node that points to that note because we need to reroute
  //Otherwise, if the present node is at the very end of the list (NULL), then n surpassed the number of indexes and nothing will be deleted
  for(int i = 0; i < n ; i++)
  { 
    if(pres != NULL){
      prev = pres;
      pres = pres->next;
    }else{
      return true;
    }
  }
  //point prev to what the present node points to 
  prev-> next = pres->next;
  delete pres;
  isDeleted = true; 
	return isDeleted;
}

// TODO: GOLD PROBLEM
// Swap the first and last nodes (don't just swap the values)
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;
    Node *temp = head;
    if(head == NULL) {
        cout << "List is empty. Cannot swap" << endl;
        return false;
    }

    // TODO (take care of the edge case when your linkedlist has just 2 nodes)
    //if head points to a node that points to NULL, then there's only two nodes in the linked list
    if(head->next->next == NULL)
    {
      //swap 1st and 2nd node 
      head = head->next;
      head->next = temp;
      head->next->next = NULL;
      temp = NULL;
      isSwapped = true;
      return isSwapped;
    }

    
    Node *temp2 = head;
    //while temp2 isn't the node pointing to the tail, iterate through the list until temp2 is
    while (temp2->next->next != NULL)
    {
      temp2 = temp2->next;
    }

    //swap nodes where temp2 is the node pointing toward tail, and temp is original head
    head = temp2->next;
    head->next = temp->next;
    temp2->next = temp;
    temp2->next->next = NULL;

    temp = NULL;
    temp2 = NULL;
    delete temp;
    delete temp2;

    isSwapped = true;
    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}
