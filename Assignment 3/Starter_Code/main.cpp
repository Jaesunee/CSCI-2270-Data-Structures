#include "SocialMediaNetwork.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{


    SocialMediaNetwork ProfileNet;
    int opt = 0; string s; string s1; string s2; string s3;

    while(opt != 5) {

        displayMenu();

        getline(cin, s);
        opt = stoi(s);

        switch(opt) {
            case 1: {
                ProfileNet.loadDefaultSetup();
                ProfileNet.printNetwork();
                break;
            }

            case 2: {
                ProfileNet.printNetwork();
                break;
            }

            case 3: {
                cout << "Enter name of the recipient to receive the message: "<< endl;
                getline(cin, s1);

                //cout << "Enter the message to send: " << endl;
                //getline(cin, s2);

                cout << endl;

                ProfileNet.transmitNumFriendsInfo(s1);

                break;
            }

            case 4: {
                cout << "Enter a new profile name: " << endl;
                getline(cin, s1);

                string numFriends;
                cout << "Enter number of friends: " << endl;
                getline(cin, numFriends);

                cout << "Enter the social media status: " << endl;
                getline(cin, s3);

                cout << "Enter the previous profile name (or First): " << endl;
                getline(cin, s2);
                
                while(!(s2 == "First" || ProfileNet.searchForProfile(s2))) {
                    cout << "INVALID(previous profile name)...Please enter a VALID profile name!" << endl;
                    getline(cin, s2);


                }

                if(s2 == "First") {
                    ProfileNet.addProfileInfo(NULL, s1, stoi(numFriends), s3);
                }
                else {
                    ProfileNet.addProfileInfo(ProfileNet.searchForProfile(s2), s1, stoi(numFriends), s3);
                }

                ProfileNet.printNetwork();
                break;
            }

            case 5: {
                cout << "Quitting..." << endl;
                break;
            }

        }
    }

    cout << "Goodbye!" << endl;

    return 0;
}




/************************************************
           Definitions for main.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Broadcast Profile Info " << endl;
    cout << " 4. Add Profile " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
