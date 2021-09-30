/************************************************************************/
/*                SocialMediaNetwork Implementation                     */
/************************************************************************/
/*    TODO: Implement the member functions of class SocialMediaNetwork  */
/*     This class uses a linked-list of SocialMediaProfile structs to   */
/*          represent communication paths between profiles              */
/************************************************************************/

#include "SocialMediaNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
SocialMediaNetwork::SocialMediaNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool SocialMediaNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new profile to the network
 *   between the profile *previous and the profile that follows it in the network.
 * @param previous      -- name of the SocialMediaProfile that comes before the new profile
 * @param profileName   -- name of the new profile
 * @param totalFriends  -- number of friends of the profile
 * @param status        -- social media status 
 * @return none
 */
void SocialMediaNetwork::addProfileInfo(SocialMediaProfile* previous, string profileName, int totalFriends, string status){
    if(previous == NULL)
    {
        cout << "adding: " << profileName << " (HEAD)" << endl;
        SocialMediaProfile* newProfile = new SocialMediaProfile;
        newProfile->next = head;
        newProfile->name = profileName;
        newProfile->socialMediaStatus = status;
        newProfile->totalFriends = totalFriends;
        head = newProfile;
    }
    else
    {
        cout << "adding: " << profileName << " (prev: " << previous->name << ")" << endl;
        SocialMediaProfile* newProfile = new SocialMediaProfile;
        newProfile->next = previous->next;
        newProfile->name = profileName;
        newProfile->socialMediaStatus = status;
        newProfile->totalFriends = totalFriends;
        previous->next = newProfile;
    }
}


/*
 * Purpose: populates the network with the predetermined profiles
 * @param none
 * @return none
 */
void SocialMediaNetwork::loadDefaultSetup()
{
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings
    deleteEntireNetwork();


    addProfileInfo(NULL, "Marshall", 10, "There is a great sandwich place on 24th.");
    addProfileInfo(searchForProfile("Marshall"), "Lily", 8, "I want to move to the suburbs");
    addProfileInfo(searchForProfile("Lily"), "Ted", 6, "Working on a building design right now.");
    addProfileInfo(searchForProfile("Ted"), "Robin", 5, "The Canucks won today.");
    addProfileInfo(searchForProfile("Robin"), "Barney", 4, "Suit up.");
    addProfileInfo(searchForProfile("Barney"), "Ranjit", 15, "NYC is an interesting city.");
}

/*
 * Purpose: Search the network for the specified profile and return a pointer to that node
 * @param profileName -- name of the profile to look for in network
 * @return pointer to node of profileName, or NULL if not found
 *
 */
SocialMediaProfile* SocialMediaNetwork::searchForProfile(string profileName)
{
    SocialMediaProfile* temp = head;
    while (temp != NULL && temp->name != profileName)
    {
        if(temp->next == NULL){
            return NULL;
        }
        temp = temp->next;
    }
    return temp;
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void SocialMediaNetwork::transmitNumFriendsInfo(string receiverProfileName) {
   SocialMediaProfile* temp = head;
    
    if (temp == NULL)
    {
        cout << "Empty List" << endl;
        return;
    }
    
    if(searchForProfile(receiverProfileName) == NULL)
    {
        cout << "Profile not Found" << endl;
        return;
    }
    
    temp = head;
    
    if (temp->name == receiverProfileName)
    {
        temp->numberMessages++;
        cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->name << " has " << temp->totalFriends << " friends." << endl;
        return;
    }
    
    while(temp->name != receiverProfileName)
    {
        temp->numberMessages++;
        cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->name << " has " << temp->totalFriends << " friends." << endl;
        if (temp->next->name == receiverProfileName){
            temp->next->numberMessages++;
            cout << temp->next->name << " [# messages received: " << temp->next->numberMessages << "] received: " << temp->next->name << " has " << temp->next->totalFriends << " friends." << endl;
            return;
        }
        temp = temp->next;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void SocialMediaNetwork::printNetwork() {
    if(head == NULL){
        cout << "== CURRENT PATH ==" << endl;
        cout << "nothing in path" << endl;
        cout << "===" << endl;
        return;
    }
    
    cout << "== CURRENT PATH ==" << endl;
    SocialMediaProfile* temp = head;
    while(temp->next != NULL){
        cout << temp->name << "(" << temp->totalFriends << ") -> ";
        temp = temp->next;
    }
    cout << temp->name << "(" << temp->totalFriends << ") -> " << "NULL" << endl;
    cout << "===" << endl;
}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the SocialMediaProfile in the network with the specified name.
 * @param profileName name of the SocialMediaProfile to delete in the network
 * @return none
 */
void SocialMediaNetwork::deleteSocialMediaProfile(string profileName) 
{
    // TODO: Complete this function 
    if (isEmpty())
    {
        cout << "Profile does not exist." << endl;
        return;
    }

    if (searchForProfile(profileName) == NULL)
    {
        cout << "Profile does not exist." << endl;
        return;
    }

    if (searchForProfile(profileName) == head)
    {
        SocialMediaProfile *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    SocialMediaProfile *prev = head;

    while(prev->next->name != profileName)
    {
        prev = prev->next;
    }

    SocialMediaProfile *curr = prev->next;
    prev->next = curr->next;
    delete curr;
}

/*
 * Purpose: deletes all SocialMediaProfiles in the network starting at the head SocialMediaProfile.
 * @param: none
 * @return: none
 */
void SocialMediaNetwork::deleteEntireNetwork()
{
    if (isEmpty())
    {
        return;
    }
     
    SocialMediaProfile *temp = head;

    while(temp != NULL)
    {
        head = head->next;
        cout << "deleting: " << temp->name << endl;
        delete temp;
        temp = head;
    }
    cout << "Deleted network" << endl;
}

/*
* Purpose: Creates a loop from last node to the SocialMediaProfile specified.
* @param profileName name of the SocialMediaProfile to loop back
* returns the last node before loop creation (to break the loop)
*/
SocialMediaProfile* SocialMediaNetwork::createLoop(string profileName) 
{
    SocialMediaProfile *tail = head;
    while(tail->next != NULL){
        tail = tail->next;
    }

    if(searchForProfile(profileName) == NULL)
    {
        return tail;
    }

    tail->next = searchForProfile(profileName);
    return tail;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected.
 */
bool SocialMediaNetwork::detectLoop() 
{
    if(head == NULL){
        return false;
    }
    
    SocialMediaProfile *slow = head;
    SocialMediaProfile *fast = head->next;
    
    while(slow != fast){
        if(fast->next == NULL || fast->next->next ==NULL){
            return false;
        }
        
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start index, end index
 * @return: none
 */
void SocialMediaNetwork::readjustNetwork(int start_index, int end_index)
{
    if(head == NULL){
        cout << "Linked List is Empty" << endl;
        return;
    }

    SocialMediaProfile *temp = head;
    int lastIndex = 0;

    while (temp->next != NULL){
        temp = temp->next;
        lastIndex++;
    }

    if(end_index >= lastIndex || end_index < 0){
        cout << "Invalid end index" << endl;
        return;
    }

    if(start_index >= lastIndex || start_index < 0){
        cout << "Invalid start index" << endl;
        return;
    }

    if(start_index > end_index){
        cout << "Invalid indices" << endl;
        return;
    }

    //FINISH
    SocialMediaProfile *tail = head;
    SocialMediaProfile *prev = head;
    SocialMediaProfile *start = head;
    SocialMediaProfile *end = head;
    SocialMediaProfile *pres = head;

    while(tail->next != NULL){
        tail = tail->next;
    }

    for(int i = 0; i < end_index; i++){
        end = end->next;
    }

    if(end->next == NULL){
        return;
    }

    if(start_index == 0)
    {
        pres = end->next;
        tail->next = head;
        end->next = NULL;
        head = pres;
        return;
    }

    for(int i = 0;i < start_index; i++)
    {
        start = start->next;
    }

    while(prev->next != start){
        prev = prev->next;
    }

    prev->next = end->next;
    tail->next = start;
    end->next = NULL;
}

/*
 * Purpose: Destructor to delete the entire list on termination
 * @param none
 * @return none
 */
SocialMediaNetwork::~SocialMediaNetwork()
{
    if (isEmpty())
    {
        return;
    }
     
    SocialMediaProfile *temp = head;

    while(temp != NULL)
    {
        head = head->next;
        cout << "deleting: " << temp->name << endl;
        delete temp;
        temp = head;
    }
    cout << "Deleted network" << endl;
}
