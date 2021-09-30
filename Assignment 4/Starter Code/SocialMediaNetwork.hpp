/****************************************************************/
/*                  SocialMediaNetwork Definition                   */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

//#pragma once
#include <iostream>
using namespace std;

// SocialMediaProfile: node struct that will be stored in the SocialMediaNetwork
struct SocialMediaProfile
{
    string name;                 // name of the person
    string socialMediaStatus;    // status set by the profile
    int numberMessages;          // no. of messages in the inbox
    SocialMediaProfile *next;    // pointer to the next profile
    int totalFriends;            // number of friends of this profile

};

// class for storing and manipulating linked-list of social media profiles
class SocialMediaNetwork {
    private:
        SocialMediaProfile* head;  // pointer to head of linked list of profiles

    public:
        // You will need to define the below unfinished methods in SocialMediaNetwork.cpp
        SocialMediaNetwork();
        bool isEmpty();
        void addProfileInfo(SocialMediaProfile* previous, string profileName, int totalFriends, string status);
        void loadDefaultSetup();
        SocialMediaProfile* searchForProfile(string profileName);
        void transmitNumFriendsInfo(string receiverProfileName);
        void printNetwork();

        /* Assignment 4: TODO */
        void deleteSocialMediaProfile(string profileName);
        void deleteEntireNetwork();
        void readjustNetwork(int start, int end);
        bool detectLoop();
        SocialMediaProfile* createLoop(std::string profileName);
        ~SocialMediaNetwork();
};
