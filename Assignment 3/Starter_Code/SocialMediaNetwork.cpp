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
void SocialMediaNetwork::loadDefaultSetup(){
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
SocialMediaProfile* SocialMediaNetwork::searchForProfile(string profileName){
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
