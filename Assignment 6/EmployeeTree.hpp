#ifndef EMPLOYEETREE_HPP
#define EMPLOYEETREE_HPP

#include <iostream>
#include <string>

using namespace std;

struct EmployeeNode {
    int empId;
    int empLevel;
    int empJoiningYear;
    string empName;
    string empPhone;

    EmployeeNode* left  = NULL;
    EmployeeNode* right = NULL;
};


class EmployeeTree{
    private:
        EmployeeNode* root;

    public:
        EmployeeTree();
        ~EmployeeTree();

        void printEmployeeDirectory();
        void addEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear);
        void findEmployee(int empId);
        void queryEmployees(int level, int year);
        void printLevelNodes(int node_level);
        int  getKthLowestEmployeeID(int k);
};

#endif