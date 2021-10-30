#include "EmployeeTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu();

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Invalid command-line arguments" << endl;
        cout << "Usage: ./a.out <EmployeeCSVFilename>" << endl;
        return 0;
    }

    // Processing the file
    ifstream fp(argv[1]);
    if (fp.fail()) {
        cout << "Error opening file." << endl;
        return 0;
    }
    
    // Declare the tree
    EmployeeTree* tree = new EmployeeTree;

    // Read from file, Build the tree
    string line, field;
    int empId, empLevel, empJoiningYear;
    string empName, empPhone;

    while (getline(fp, line)) {
        istringstream ss(line);

        getline(ss, field, ','); empId = stoi(field);
        getline(ss, field, ','); empName = field;
        getline(ss, field, ','); empLevel = stoi(field);
        getline(ss, field, ','); empPhone = field;
        getline(ss, field, ','); empJoiningYear = stoi(field);

        tree->addEmployee(empId, empName, empLevel, empPhone, empJoiningYear);
    }
    fp.close();

    // Interactive menu starts here
    int input = 0;
    do {

        displayMenu();
        getline(cin, line);
        input = stoi(line);

        if (input == 1)
        {
            cout << "Enter empId: ";
            getline(cin, field); int toSearch = stoi(field);

            tree->findEmployee(toSearch);
        }
        else if (input == 2)
        {
            cout << "Enter empJoiningYear: ";
            getline(cin, field); int y = stoi(field);

            cout << "Enter empLevel: ";
            getline(cin, field); int l = stoi(field);

            tree->queryEmployees(l, y);
        }
        else if (input == 3)
        {
            tree->printEmployeeDirectory();
        }
        else if (input == 4)
        {
            cout << "Enter K: ";
            getline(cin, field); int k = stoi(field);

            int x = tree->getKthLowestEmployeeID(k);
            cout << "K lowest empID: " << x << endl;
        }
        else if (input == 5)
        {
            cout << "Enter K: ";
            getline(cin, field); int k = stoi(field);

            tree->printLevelNodes(k);
        }
        else if (input == 6)
        {
            cout << "Exiting program." << endl;
        }
        else
        {
            cout << "Invalid input. Try again." << endl;
        }

        cout << endl;

    } while(input != 6);

    return 0;
}

void displayMenu() {
    cout << "====== Main Menu ======" << endl;
    cout << "1. Find an employee" << endl;
    cout << "2. Query employees with year and level" << endl;
    cout << "3. Print the directory" << endl;
    cout << "4. Get an employee with Kth lowest empId" << endl;
    cout << "5. Print employees at tree level K" << endl;
    cout << "6. Quit" << endl;
    cout << "SELECT: ";
}

