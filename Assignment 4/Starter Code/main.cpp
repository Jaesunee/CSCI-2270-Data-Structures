/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SocialMediaNetwork.hpp"

using namespace std;

void displayMenu();
void handleUserInput(SocialMediaNetwork& profileNet);

int main(int argc, char* argv[])
{
    // Object representing our list of SocialMediaProfile(s).
    SocialMediaNetwork profileNet;

    // This will loop until user selects quit option
    handleUserInput(profileNet);

    // quit: clean up!
    profileNet.printNetwork();

    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param profileNet object for carrying out profile network operations
 * @return none
 */
void handleUserInput(SocialMediaNetwork& profileNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            case 1: {
                //build network
                profileNet.loadDefaultSetup();
                profileNet.printNetwork();

                break;
            }

            case 2: {
                //print path
                profileNet.printNetwork();

                break;
            }

            case 3: {
                // add profile
                string name, numFriends, status, prevName;

                cout << "Enter a new profile name: " << endl;
                getline(cin, name);

                cout << "Enter number of friends: " << endl;
                getline(cin, numFriends);

                cout << "Enter the social media status: " << endl;
                getline(cin, status);

                cout << "Enter the previous profile name (or First): " << endl;
                getline(cin, prevName);
                
                while(!(prevName == "First" || profileNet.searchForProfile(prevName))) {
                    cout << "INVALID(previous profile name)...Please enter a VALID profile name!" << endl;
                    getline(cin, prevName);


                }

                if(prevName == "First") {
                    profileNet.addProfileInfo(NULL, name, stoi(numFriends), status);
                }
                else {
                    profileNet.addProfileInfo(profileNet.searchForProfile(prevName), name, stoi(numFriends), status);
                }

                profileNet.printNetwork();
                break;
            }

            case 4: {
                // delete profile
                string profileName;
                cout << "Enter a profile name: " << endl;
                getline(cin, profileName);

                profileNet.deleteSocialMediaProfile(profileName);

                profileNet.printNetwork();

                break;
            }

            case 5: {
                // detect loop
                string profile;
                cout << "Enter the profile name to loop back: " <<endl;
                getline(cin, profile);

                SocialMediaProfile* lastnode = profileNet.createLoop(profile);

                bool hasLoop = profileNet.detectLoop();

                if (hasLoop) {
                    cout << "Network contains a loop" << endl;
                    cout << "Breaking the loop"<< endl;
                    lastnode->next = NULL;
                } else {
                    cout << "Network does not contain a loop" << endl;
                }

                break;
            }

            case 6: {
                //re-adjust network
                string st, en;
                cout << "Enter the start index: " << endl;
                getline(cin, st);
                cout << "Enter the end index: " << endl;
                getline(cin, en);

                profileNet.readjustNetwork(stoi(st), stoi(en));

                profileNet.printNetwork();

                break;
            }

            case 7: {
                // delete entire network
                cout << "Network before deletion" << endl;
                profileNet.printNetwork();

                profileNet.deleteEntireNetwork();

                cout << "Network after deletion" <<endl;
                profileNet.printNetwork();

                break;
            }
            case 8: {
                // quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;
            }

            default:     // invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Profile " << endl;
    cout << " 4. Delete Profile " << endl;
    cout << " 5. Detect loop in Network" << endl;
    cout << " 6. Re-adjust Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
